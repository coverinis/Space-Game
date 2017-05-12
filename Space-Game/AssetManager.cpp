/*
* FILE          : AssetManager.cpp
* PROJECT       : PROG2215 - SET Trek
* PROGRAMMER    : Shawn Coverini
* FIRST VERSION : 02-XX-2017
* DESCRIPTION   : Load and Manage game assets
*/
#include "AssetManager.h"


AssetManager::AssetManager(wchar_t* file_name, RenderManager* render_manager, float r, float g, float b, float t)
{
	render_manager_ = render_manager; //render manager
	bitmap_ = NULL;                   //set to null for "empty" space
	HRESULT hr;                       //HRESULT is used for error checking

	//Create a WIC factory
	IWICImagingFactory2 *iwic_imaging_factory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,       //WIC factory CLSID 
		NULL,                          //Not part of an aggragator
		CLSCTX_INPROC_SERVER,          //Context of how code will run
		IID_IWICImagingFactory,	       //Reference to inteerface
		(LPVOID*)&iwic_imaging_factory //Pointer to factory
	);

	//Create decoder
	IWICBitmapDecoder *iwic_bitmap_decoder = NULL;
	hr = iwic_imaging_factory->CreateDecoderFromFilename(
		file_name,                    //File name
		NULL,                         //No prefered vendor
		GENERIC_READ,                 //Read the file
		WICDecodeMetadataCacheOnLoad, //Cache on load
		&iwic_bitmap_decoder          //Pointer to decoder
	);

	//Read a frame
	IWICBitmapFrameDecode *iwic_bitmap_frame = NULL;
	hr = iwic_bitmap_decoder->GetFrame(0, &iwic_bitmap_frame);

	//Create converter
	IWICFormatConverter *iwic_format_converter = NULL;
	hr = iwic_imaging_factory->CreateFormatConverter(&iwic_format_converter);

	//Init converter
	hr = iwic_format_converter->Initialize(
		iwic_bitmap_frame,             //Frame
		GUID_WICPixelFormat32bppPBGRA, //Pixle format
		WICBitmapDitherTypeNone,       //Only used for indexed palettes
		NULL,                          //Only used for indexed palettes
		0.0,                           //Only used for indexed palettes
		WICBitmapPaletteTypeCustom     //Only used for indexed palettes
	);

	//Convert to D2D1Bitmap
	hr = render_manager->GetRenderTarget()->CreateBitmapFromWicBitmap(
		iwic_format_converter, //Converter
		NULL,                  //Bitmap properties
		&bitmap_               //Destination of bitmap
	);

	/*Reference : Microsoft. (n.d.). Chroma-key Effect (Windows). Retrieved February 18, 2017,
	*            from https://msdn.microsoft.com/ko-kr/dn890715 */

	//Create Chroma Key
	ID2D1Effect* effect_chroma_key;
	render_manager->GetRenderTarget()->CreateEffect(CLSID_D2D1ChromaKey, &effect_chroma_key);
	D2D1_VECTOR_3F vector_chroma;
	vector_chroma.x = r;
	vector_chroma.y = g;
	vector_chroma.z = b;
	effect_chroma_key->SetInput(0, bitmap_);
	effect_chroma_key->SetValue(D2D1_CHROMAKEY_PROP_COLOR, vector_chroma);
	effect_chroma_key->SetValue(D2D1_CHROMAKEY_PROP_TOLERANCE, t);
	effect_chroma_key->SetValue(D2D1_CHROMAKEY_PROP_FEATHER, true);
	effect_chroma_key->SetValue(D2D1_CHROMAKEY_PROP_INVERT_ALPHA, false);
	effect_chroma_key->GetOutput(&image_);

	//Change colour for ship detail
	if (file_name == L"ShipDetail.bmp")
	{
		ID2D1Effect* colorMatrixEffect;
		render_manager->GetRenderTarget()->CreateEffect(CLSID_D2D1ColorMatrix, &colorMatrixEffect);

		colorMatrixEffect->SetInput(0, image_);
		D2D1_MATRIX_5X4_F matrix = D2D1::Matrix5x4F(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0);
		colorMatrixEffect->SetValue(D2D1_COLORMATRIX_PROP_COLOR_MATRIX, matrix);
		colorMatrixEffect->GetOutput(&image_);

		if (colorMatrixEffect) colorMatrixEffect->Release();
	}

	//Scale images
	ID2D1Effect* effect_scale;

	render_manager->GetRenderTarget()->CreateEffect(CLSID_D2D1Scale, &effect_scale);
	effect_scale->SetInput(0, image_);
	effect_scale->SetValue(D2D1_SCALE_PROP_CENTER_POINT, D2D1::Vector2F(0.0, 0.0));
	//Calculate scale ratio
	effect_scale->SetValue(D2D1_SCALE_PROP_SCALE, D2D1::Vector2F((D_WIDTH / MAX_GRID)/bitmap_->GetSize().width, (D_HEIGHT / MAX_GRID)/bitmap_->GetSize().height));
	effect_scale->GetOutput(&image_);

	//Releas COM objects
	if (iwic_format_converter) iwic_format_converter->Release();
	if (iwic_bitmap_decoder) iwic_bitmap_decoder->Release();
	if (iwic_bitmap_frame) iwic_bitmap_frame->Release();
	if (iwic_imaging_factory) iwic_imaging_factory->Release();
	if (effect_scale) effect_scale->Release();
	if (effect_chroma_key) effect_chroma_key->Release();
}

AssetManager::~AssetManager()
{
	if (bitmap_) bitmap_->Release();
	if (image_) image_->Release();
}

void AssetManager::Draw()
{
	render_manager_->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(0, D2D1::Point2F(0,0)));
	render_manager_->GetRenderTarget()->DrawBitmap(
		bitmap_,                                                                         //Bitmap
		D2D1::RectF(0.0f, 0.0f,	                                                         //Rectangle to render to
			bitmap_->GetSize().width,
			bitmap_->GetSize().height),
		1.0f,                                                                            //Opacity
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, //Interpolation
		D2D1::RectF(0.0f, 0.0f,                                                          //Source rectangle
			bitmap_->GetSize().width,
			bitmap_->GetSize().height)
	);
}

void AssetManager::Draw(float x, float y, float angle)
{
	render_manager_->GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(x + O_CENTER_X, y + O_CENTER_Y)));
	render_manager_->GetRenderTarget()->DrawImage(
		image_,
		D2D1::Point2F(x, y),
		D2D1::RectF(0.0f, 0.0f,
			D_WIDTH / MAX_GRID,
			D_HEIGHT / MAX_GRID
		),
		D2D1_INTERPOLATION_MODE_ANISOTROPIC,
		D2D1_COMPOSITE_MODE_SOURCE_OVER
	);
}
