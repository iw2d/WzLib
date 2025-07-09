#import "./IWzArchive.tlb" no_namespace
#import "./IWzSeekableArchive.tlb" no_namespace, exclude("IWzArchive")
#import "./IWzSerialize.tlb" no_namespace, exclude("IWzArchive")
#import "./IWzProperty.tlb" no_namespace, exclude("IWzArchive", "IWzSerialize")
#import "./IWzNameSpace.tlb" no_namespace
#import "./IWzWritableNameSpace.tlb" no_namespace, exclude("IWzNameSpaceProperty", "IWzNameSpace")
#import "./IWzPackage.tlb" no_namespace, exclude("IWzArchive", "IWzSeekableArchive", "IWzNameSpaceProperty", "IWzNameSpace")
#import "./IWzFileSystem.tlb" no_namespace, exclude("IWzNameSpaceProperty", "IWzNameSpace", "IWzWritableNameSpace")
#import "./IWzResMan.tlb" no_namespace, exclude("IWzArchive"), rename("GetObject", "GetObjectA")
#import "./IWzUOL.tlb" no_namespace, exclude("IWzArchive", "IWzSerialize")
#import "./IWzCanvas.tlb" no_namespace, exclude("tagRECT", "IWzArchive", "IWzSerialize", "IWzProperty"), rename("DrawText", "DrawTextA")
#import "./IWzSound.tlb" no_namespace, exclude("IWzArchive", "IWzSerialize")
#import "./IWzShape2D.tlb" no_namespace, exclude("IWzArchive", "IWzSerialize")
#import "./IWzConvex2D.tlb" no_namespace, exclude("IWzArchive", "IWzSerialize", "IWzShape2D")
#import "./IWzVector2D.tlb" no_namespace, exclude("IWzArchive", "IWzSerialize", "IWzShape2D")
#import "./IWzGr2D.tlb" no_namespace, exclude("tagRECT", "IWzArchive", "IWzSerialize", "IWzProperty", "IWzRawCanvasAllocator", "IWzRawCanvas", "IWzFont", "IWzCanvas", "CANVAS_ALPHATYPE", "CANVAS_LEVELMAP", "CANVAS_PIXFORMAT", "CANVAS_DITHERTYPE", "IWzShape2D", "IWzVector2D")


extern "C" __declspec(dllexport) void GenerateImports() {
}