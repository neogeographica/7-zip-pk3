// Pk3Stream.h

#ifndef __PK3_STREAM_H
#define __PK3_STREAM_H

#include "../../../Common/MyCom.h"
#include "../../IStream.h"


class CPk3InStream:
    public IInStream,
    public CMyUnknownImp
{
public:
    MY_UNKNOWN_IMP1(IInStream)
    STDMETHOD(Read)(void *data, UInt32 size, UInt32 *processedSize);
    STDMETHOD(Seek)(Int64 offset, UInt32 seekOrigin, UInt64 *newPosition);
    CPk3InStream(IInStream *stream);
private:
    CMyComPtr<IInStream> _stream;
    UInt64 _pos;
};

#define STAGING_BUFFER_SIZE (64 * 1024)

class CPk3OutStream:
    public IOutStream,
    public CMyUnknownImp
{
public:
    MY_UNKNOWN_IMP1(IOutStream)
    STDMETHOD(Write)(const void *data, UInt32 size, UInt32 *processedSize);
    STDMETHOD(Seek)(Int64 offset, UInt32 seekOrigin, UInt64 *newPosition);
    STDMETHOD(SetSize)(UInt64 newSize);
    CPk3OutStream(IOutStream *stream);
private:
    CMyComPtr<IOutStream> _stream;
    UInt64 _pos;
    Byte _staging[STAGING_BUFFER_SIZE];
};

#endif
