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
    // QueryInterface & refcounting support
    MY_UNKNOWN_IMP1(IInStream)
    // methods for declared interfaces
    STDMETHOD(Read)(void *data, UInt32 size, UInt32 *processedSize);
    STDMETHOD(Seek)(Int64 offset, UInt32 seekOrigin, UInt64 *newPosition);
    // constructor
    CPk3InStream(IInStream *stream);
private:
    // All interface invocations will be passed to the "real" input stream to
    // handle, but we'll track the current position in the stream and use
    // that to do the QuakeLive XOR on data that comes from that stream.
    CMyComPtr<IInStream> _stream;
    UInt64 _pos;
};

// As long as this is moderately large, the compression time doesn't appear to
// be too sensitive to the buffer size. I did some quick tests creating a pk3
// (from the QL version of jlctf2), doing 5 reps with each buffer size and
// averaging the times:
//     1 kB: 685ms
//     4 kB: 607ms
//    16 kB: 558ms
//    64 kB: 566ms
//   512 kB: 572ms
#define STAGING_BUFFER_SIZE (16 * 1024)

class CPk3OutStream:
    public IOutStream,
    public CMyUnknownImp
{
public:
    // QueryInterface & refcounting support
    MY_UNKNOWN_IMP1(IOutStream)
    // methods for declared interfaces
    STDMETHOD(Write)(const void *data, UInt32 size, UInt32 *processedSize);
    STDMETHOD(Seek)(Int64 offset, UInt32 seekOrigin, UInt64 *newPosition);
    STDMETHOD(SetSize)(UInt64 newSize);
    // constructor
    CPk3OutStream(IOutStream *stream);
private:
    // All interface invocations will be passed to the "real" output stream to
    // handle, but we'll track the current position in the stream and use
    // that to do the QuakeLive XOR on data sent to that stream. To avoid
    // changing the source data, we'll stage the XOR changes into our own
    // buffer.
    CMyComPtr<IOutStream> _stream;
    UInt64 _pos;
    Byte _staging[STAGING_BUFFER_SIZE];
};

#endif
