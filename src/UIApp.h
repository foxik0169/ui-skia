#pragma once 

/*
	UI App 
	------

	Tool to debug/test Skia backend.


	@FoXik0169
*/

#include "SkSurface.h"
#include "SkWindow.h"

class GrContext;
struct GrGLInterface;
class GrRenderTarget;
class SkCanvas;

class UIAppWindow : public SkOSWindow {
public:
	enum UIRender {
		R_Raster,
		R_GPU
	};

	UIAppWindow(void* hwnd);
	virtual ~UIAppWindow() override;

protected:
	SkSurface* createSurface() override {
		SkSurfaceProps props(Super::getSurfaceProps());
		if (R_GPU == fRender) {
			return SkSurface::NewRenderTargetDirect(fRenderTarget, &props);
		}
		static const SkImageInfo info = SkImageInfo::MakeN32Premul(
			SkScalarRoundToInt(this->width()), SkScalarRoundToInt(this->height()));
		return fSurface = SkSurface::NewRaster(info, &props);
	}

	UIRender fRender;

	void onSizeChange() override;
	void draw(SkCanvas* canvas) override;

private:
	
	bool SetupBackend();

	SkSurface* fSurface;
	GrContext* fContext;
	GrRenderTarget* fRenderTarget;

	AttachmentInfo fAttachmentInfo;
	
	const GrGLInterface* fInterface;

	typedef SkOSWindow Super;
};