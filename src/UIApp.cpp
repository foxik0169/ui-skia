#include "UIApp.h"

#include "gl/GrGLInterface.h"
#include "GrContext.h"
#include "SkApplication.h"
#include "SkCanvas.h"
#include "SkGradientShader.h"
#include "SkGraphics.h"
#include "SkGr.h"

void application_init() {
	SkGraphics::Init();
	SkEvent::Init();
}

void application_term() {
	SkEvent::Term();
}

SkOSWindow* create_sk_window(void* hwnd, int, char**) {
	return new UIAppWindow(hwnd);
}


UIAppWindow::UIAppWindow(void * hwnd) : Super(hwnd)
{
	fRender = R_GPU;
	fRenderTarget = nullptr;
	setTitle("UI App - Skia debug");
	SetupBackend();
}

UIAppWindow::~UIAppWindow()
{
	SkSafeUnref(fContext);
	fContext = nullptr;

	SkSafeUnref(fInterface);
	fInterface = nullptr;

	SkSafeUnref(fRenderTarget);
	fRenderTarget = nullptr;

	Super::detach();
}

void UIAppWindow::onSizeChange()
{
	SetupBackend();
}

void UIAppWindow::draw(SkCanvas * canvas)
{
	canvas->drawColor(SK_ColorBLUE);
	fContext->flush();
	inval(nullptr);

	Super::present();
}

bool UIAppWindow::SetupBackend()
{
	setVisibleP(true);
	setClipToBounds(false);

	bool result = attach(kNativeGL_BackEndType, 2 /*msaa*/, &fAttachmentInfo);
	if (false == result) {
		SkDebugf("Couldn't create backend.\n");
		detach();
		return false;
	}

	fInterface = GrGLCreateNativeInterface();

	SkASSERT(NULL != fInterface);

	fContext = GrContext::Create(kOpenGL_GrBackend, (GrBackendContext)fInterface);
	SkASSERT(NULL != fContext);

	SkSafeUnref(fRenderTarget);
	fRenderTarget = renderTarget(fAttachmentInfo, fInterface, fContext);

	return true;
}
