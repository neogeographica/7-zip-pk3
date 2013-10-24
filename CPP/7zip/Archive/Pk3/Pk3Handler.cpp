// Pk3Handler.cpp

#include "StdAfx.h"
#include "Pk3Handler.h"
#include "Pk3Stream.h"


using namespace NWindows;

namespace NArchive {
namespace NPk3 {

CHandler::CHandler()
{
    m_Delegate = new NArchive::NZip::CHandler();
}

// INTERFACE_IInArchive

STDMETHODIMP CHandler::Open(IInStream *inStream,
    const UInt64 *maxCheckStartPosition, IArchiveOpenCallback *callback)
{
    CMyComPtr<CPk3InStream> pk3InStream = new CPk3InStream(inStream);
    return m_Delegate->Open(pk3InStream, maxCheckStartPosition, callback);
}

STDMETHODIMP CHandler::Close()
{
    return m_Delegate->Close();
}

STDMETHODIMP CHandler::GetNumberOfItems(UInt32 *numItems)
{
    return m_Delegate->GetNumberOfItems(numItems);
}

STDMETHODIMP CHandler::GetProperty(UInt32 index, PROPID propID,
    PROPVARIANT *value)
{
    return m_Delegate->GetProperty(index, propID, value);
}

STDMETHODIMP CHandler::Extract(const UInt32 *indices, UInt32 numItems,
    Int32 testMode, IArchiveExtractCallback *extractCallback)
{
    return m_Delegate->Extract(indices, numItems, testMode, extractCallback);
}

STDMETHODIMP CHandler::GetArchiveProperty(PROPID propID, PROPVARIANT *value)
{
    return m_Delegate->GetArchiveProperty(propID, value);
}

STDMETHODIMP CHandler::GetNumberOfProperties(UInt32 *numProperties)
{
    return m_Delegate->GetNumberOfProperties(numProperties);
}

STDMETHODIMP CHandler::GetPropertyInfo(UInt32 index, BSTR *name,
    PROPID *propID, VARTYPE *varType)
{
    return m_Delegate->GetPropertyInfo(index, name, propID, varType);
}

STDMETHODIMP CHandler::GetNumberOfArchiveProperties(UInt32 *numProperties)
{
    return m_Delegate->GetNumberOfArchiveProperties(numProperties);
}

STDMETHODIMP CHandler::GetArchivePropertyInfo(UInt32 index, BSTR *name,
    PROPID *propID, VARTYPE *varType)
{
    return m_Delegate->GetArchivePropertyInfo(index, name, propID, varType);
}

// INTERFACE_IOutArchive

STDMETHODIMP CHandler::UpdateItems(ISequentialOutStream *outStream,
    UInt32 numItems, IArchiveUpdateCallback *callback)
{
    // Zip code wants this stream to support the IOutStream interface.
    CMyComPtr<IOutStream> outStreamReal;
    outStream->QueryInterface(IID_IOutStream, (void **)&outStreamReal);
    if (!outStreamReal)
    {
        return E_NOTIMPL;
    }
    CMyComPtr<CPk3OutStream> pk3OutStream = new CPk3OutStream(outStreamReal);
    return m_Delegate->UpdateItems(pk3OutStream, numItems, callback);
}

STDMETHODIMP CHandler::GetFileTimeType(UInt32 *timeType)
{
    return m_Delegate->GetFileTimeType(timeType);
}

// STDMETHOD(SetProperties)

STDMETHODIMP CHandler::SetProperties(const wchar_t **names,
    const PROPVARIANT *values, Int32 numProperties)
{
    return m_Delegate->SetProperties(names, values, numProperties);
}

// DECL_ISetCompressCodecsInfo

#ifdef EXTERNAL_CODECS
STDMETHODIMP CHandler::SetCompressCodecsInfo(ICompressCodecsInfo *compressCodecsInfo)
{
    return m_Delegate->SetCompressCodecsInfo(compressCodecsInfo);
}
#endif

}}
