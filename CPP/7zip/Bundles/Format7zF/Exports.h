#pragma once

#include "../../../../C/7zTypes.h"
#include "../../../../C/7zVersion.h"
#include "../../Archive/ArchiveExports.h"

using namespace std;


extern "C" {

	__declspec(dllexport) char* stringEcho(char* inputString);

	__declspec(dllexport) void getLibVersion(Int32 *major, Int32 *minor, Int32 *build);

	__declspec(dllexport) Int32 getRegisteredArcCount();

	__declspec(dllexport) CArcInfo getArcInfo(Int32 arcIndex);

	__declspec(dllexport) CArcInfo* getArcInfoFromId(Byte arcId);


    // IOutArchive function wrappers

    __declspec(dllexport) ULONG outArcAddRef(IOutArchive *arc) {
        return arc->AddRef();
    }
    __declspec(dllexport) HRESULT outArcGetFileTimeType(IOutArchive *arc, UInt32 *type) {
        return arc->GetFileTimeType(type);
    }
    __declspec(dllexport) ULONG outArcRelease(IOutArchive *arc) {
        return arc->Release();
    }
    __declspec(dllexport) HRESULT outArcUpdateItems(IOutArchive *arc, ISequentialOutStream *outStream, UInt32 numItems, IArchiveUpdateCallback *callback) {
        return arc->UpdateItems(outStream, numItems, callback);
    }
    __declspec(dllexport) HRESULT outArcQueryInterface2(IOutArchive *arc, GUID &guid, void **ppvObject) {
        return arc->QueryInterface(guid, ppvObject);
    }
    /*__declspec(dllexport) HRESULT outArcQueryInterface(IOutArchive *arc, void **pp) {
        return arc->QueryInterface(pp);
    }*/

    typedef HRESULT (__stdcall *SetTotalFunc)(UInt64 total);
    typedef HRESULT(__stdcall *SetCompletedFunc)(const UInt64 *completeValue);
    typedef HRESULT(__stdcall *GetStreamFunc)(UInt32 index, ISequentialOutStream **outStream, Int32 askExtractMode);
    typedef HRESULT(__stdcall *PrepareOperationFunc)(Int32 askExtractMode);
    typedef HRESULT(__stdcall *SetOperationResultFunc)(Int32 opRes);
    typedef HRESULT(__stdcall *QueryInterfaceFunc)(const IID &riid, void **ppvObject);
    typedef ULONG(__stdcall *AddRefFunc)();
    typedef ULONG(__stdcall *ReleaseFunc)();

    struct ArchiveExtractCallbackPassthrough : public IArchiveExtractCallback
    {
        SetTotalFunc SetTotalFunc;
        HRESULT __stdcall SetTotal(UInt64 total) { return SetTotalFunc(total); }

        SetCompletedFunc SetCompletedFunc;
        HRESULT __stdcall SetCompleted(const UInt64 *completeValue) { return SetCompletedFunc(completeValue); }

        GetStreamFunc GetStreamFunc;
        HRESULT __stdcall GetStream(UInt32 index, ISequentialOutStream **outStream, Int32 askExtractMode) { return GetStreamFunc(index, outStream, askExtractMode); }
        
        PrepareOperationFunc PrepareOperationFunc;
        HRESULT __stdcall PrepareOperation(Int32 askExtractMode) { return PrepareOperationFunc(askExtractMode); }

        SetOperationResultFunc SetOperationResultFunc;
        HRESULT __stdcall SetOperationResult(Int32 opRes) { return SetOperationResultFunc(opRes); }

        QueryInterfaceFunc QueryInterfaceFunc;
        HRESULT __stdcall QueryInterface(const IID &riid, void **ppvObject) { return QueryInterfaceFunc(riid, ppvObject); }

        AddRefFunc AddRefFunc;
        ULONG __stdcall AddRef() { return AddRefFunc(); }

        ReleaseFunc ReleaseFunc;
        ULONG __stdcall Release() { return ReleaseFunc(); }
    };

    // IArchiveExtractCallback wrapper
    __declspec(dllexport) IArchiveExtractCallback* createArcExtractCallback(
        SetTotalFunc setTotalFunc, SetCompletedFunc setCompletedFunc, GetStreamFunc getStreamFunc,
        PrepareOperationFunc prepareOperationFunc, SetOperationResultFunc setOperationResultFunc,
        QueryInterfaceFunc queryInterfaceFunc, AddRefFunc addRefFunc, ReleaseFunc releaseFunc)
    {
        ArchiveExtractCallbackPassthrough cb = { };
        cb.SetTotalFunc = setTotalFunc;
        cb.SetCompletedFunc = setCompletedFunc;
        cb.GetStreamFunc = getStreamFunc;
        cb.PrepareOperationFunc = prepareOperationFunc;
        cb.SetOperationResultFunc = setOperationResultFunc;
        cb.QueryInterfaceFunc = queryInterfaceFunc;
        cb.AddRefFunc = addRefFunc;
        cb.ReleaseFunc = releaseFunc;
        return &cb;
    }

    // IInArchive function wrappers

    __declspec(dllexport) ULONG inArcAddRef(IInArchive *arc) {
        return arc->AddRef();
    }
    __declspec(dllexport) HRESULT inArcExtract(IInArchive *arc, const UInt32* indices, UInt32 numItems, Int32 testMode, IArchiveExtractCallback *extractCallback) {
        return arc->Extract(indices, numItems, testMode, extractCallback);
    }
    __declspec(dllexport) HRESULT inArcClose(IInArchive *arc) {
        return arc->Close();
    }
    __declspec(dllexport) HRESULT inArcGetArchiveProperty(IInArchive *arc, PROPID propID, PROPVARIANT *value) {
        return arc->GetArchiveProperty(propID, value);
    }
    __declspec(dllexport) HRESULT inArcGetArchivePropertyInfo(IInArchive *arc, UInt32 index, BSTR *name, PROPID *propID, VARTYPE *varType) {
        return arc->GetPropertyInfo(index, name, propID, varType);
    }
    __declspec(dllexport) HRESULT inArcGetNumberOfArchiveProperties(IInArchive *arc, UInt32 *numProps) {
        return arc->GetNumberOfArchiveProperties(numProps);
    }
    __declspec(dllexport) HRESULT inArcGetNumberOfItems(IInArchive *arc, UInt32 *numItems) {
        return arc->GetNumberOfItems(numItems);
    }
    __declspec(dllexport) HRESULT inArcGetNumberOfProperties(IInArchive *arc, UInt32 *numProps) {
        return arc->GetNumberOfProperties(numProps);
    }
    __declspec(dllexport) HRESULT inArcGetProperty(IInArchive *arc, UInt32 index, PROPID propID, PROPVARIANT *value) {
        return arc->GetProperty(index, propID, value);
    }
    __declspec(dllexport) HRESULT inArcGetPropertyInfo(IInArchive *arc, UInt32 index, BSTR *name, PROPID *propID, VARTYPE *varType) {
        return arc->GetPropertyInfo(index, name, propID, varType);
    }
    __declspec(dllexport) HRESULT inArcOpen(IInArchive *arc, IInStream *inStream, const UInt64 *maxCheckStartPosition, IArchiveOpenCallback *callback) {
        return arc->Open(inStream, maxCheckStartPosition, callback);
    }
    __declspec(dllexport) ULONG inArcRelease(IInArchive *arc) {
        return arc->Release();
    }
    __declspec(dllexport) HRESULT inArcQueryInterface2(IInArchive *arc, GUID &guid, void **ppvObject) {
        return arc->QueryInterface(guid, ppvObject);
    }
    /*__declspec(dllexport) HRESULT inArcQueryInterface(IInArchive *arc, void **pp) {
        return arc->QueryInterface(pp);
    }*/
}