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
    MY_QUERYINTERFACE_BEGIN2(IInArchive)
    MY_QUERYINTERFACE_ENTRY(IOutArchive)
    MY_QUERYINTERFACE_ENTRY(ISetProperties)
    QUERY_ENTRY_ISetCompressCodecsInfo
    MY_QUERYINTERFACE_END
    MY_ADDREF_RELEASE
    INTERFACE_IInArchive(;)
    INTERFACE_IOutArchive(;)
    STDMETHOD(SetProperties)(const wchar_t **names, const PROPVARIANT *values, Int32 numProperties);
    DECL_ISetCompressCodecsInfo
    CHandler();
private:
    CMyComPtr<NArchive::NZip::CHandler> m_Delegate;
};

}}

#endif
