// Pk3Handler.h

#ifndef __PK3_HANDLER_H
#define __PK3_HANDLER_H

#include "Common/DynamicBuffer.h"
#include "../../ICoder.h"
#include "../IArchive.h"
#include "../../Common/CreateCoder.h"
#include "../Zip/ZipHandler.h"


namespace NArchive {
namespace NPk3 {

class CHandler:
    public IInArchive,
    public IOutArchive,
    public ISetProperties,
    PUBLIC_ISetCompressCodecsInfo
    public CMyUnknownImp
{
public:
    // QueryInterface support
    MY_QUERYINTERFACE_BEGIN2(IInArchive)
    MY_QUERYINTERFACE_ENTRY(IOutArchive)
    MY_QUERYINTERFACE_ENTRY(ISetProperties)
    QUERY_ENTRY_ISetCompressCodecsInfo
    MY_QUERYINTERFACE_END
    // refcounting support
    MY_ADDREF_RELEASE
    // methods for declared interfaces
    INTERFACE_IInArchive(;)
    INTERFACE_IOutArchive(;)
    STDMETHOD(SetProperties)(const wchar_t **names, const PROPVARIANT *values, Int32 numProperties);
    DECL_ISetCompressCodecsInfo
    // constructor
    CHandler();
private:
    // All the heavy lifting will be performed by the Zip code; we'll
    // instantiate a copy of the Zip handler and pass all interface
    // invocations to it.
    CMyComPtr<NArchive::NZip::CHandler> m_Delegate;
};

}}

#endif
