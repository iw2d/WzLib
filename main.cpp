#define IMPORT_CONFIG no_namespace
#import "./IWzArchive.tlb" IMPORT_CONFIG
#import "./IWzSeekableArchive.tlb" IMPORT_CONFIG, exclude("IWzArchive")
#import "./IWzSerialize.tlb" IMPORT_CONFIG, exclude("IWzArchive")
#import "./IWzProperty.tlb" IMPORT_CONFIG, exclude("IWzArchive", "IWzSerialize")
#import "./IWzNameSpace.tlb" IMPORT_CONFIG
#import "./IWzWritableNameSpace.tlb" IMPORT_CONFIG, exclude("IWzNameSpaceProperty", "IWzNameSpace")
#import "./IWzPackage.tlb" IMPORT_CONFIG, exclude("IWzArchive", "IWzSeekableArchive", "IWzNameSpaceProperty", "IWzNameSpace")
#import "./IWzFileSystem.tlb" IMPORT_CONFIG, exclude("IWzNameSpaceProperty", "IWzNameSpace", "IWzWritableNameSpace")
#import "./IWzResMan.tlb" IMPORT_CONFIG, exclude("IWzArchive"), rename("GetObject", "GetObjectA")
#import "./IWzUOL.tlb" IMPORT_CONFIG, exclude("IWzArchive", "IWzSerialize")
#import "./IWzCanvas.tlb" IMPORT_CONFIG, exclude("tagRECT", "IWzArchive", "IWzSerialize", "IWzProperty"), rename("DrawText", "DrawTextA")
#import "./IWzSound.tlb" IMPORT_CONFIG, exclude("IWzArchive", "IWzSerialize")
#import "./IWzShape2D.tlb" IMPORT_CONFIG, exclude("IWzArchive", "IWzSerialize")
#import "./IWzConvex2D.tlb" IMPORT_CONFIG, exclude("IWzArchive", "IWzSerialize", "IWzShape2D")
#import "./IWzVector2D.tlb" IMPORT_CONFIG, exclude("IWzArchive", "IWzSerialize", "IWzShape2D")
#import "./IWzGr2DLayer.tlb" IMPORT_CONFIG, exclude("tagRECT", "IWzArchive", "IWzSerialize", "IWzProperty", "IWzRawCanvasAllocator", "IWzRawCanvas", "IWzFont", "IWzCanvas", "CANVAS_ALPHATYPE", "CANVAS_LEVELMAP", "CANVAS_PIXFORMAT", "CANVAS_DITHERTYPE", "IWzShape2D", "IWzVector2D")
#import "./IWzGr2D.tlb" IMPORT_CONFIG, exclude("tagRECT", "IWzArchive", "IWzSerialize", "IWzProperty", "IWzRawCanvasAllocator", "IWzRawCanvas", "IWzFont", "IWzCanvas", "CANVAS_ALPHATYPE", "CANVAS_LEVELMAP", "CANVAS_PIXFORMAT", "CANVAS_DITHERTYPE", "IWzShape2D", "IWzVector2D", "IWzGr2DLayer", "LAYER_BLENDTYPE", "GR2D_ANITYPE")


extern "C" __declspec(dllexport) void GenerateImports() {
}