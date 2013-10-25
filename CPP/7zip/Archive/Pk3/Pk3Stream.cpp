// Pk3Stream.cpp

#include "StdAfx.h"
#include "Pk3Stream.h"


// QuakeLive XOR pattern from Luigi Auriemma (cf. quakelivedec).
static const Byte quakeliveXor[] =
        "\xcf\x8e\x8e\x4c\xd0\xd9\x30\xce\x07\x32\x27\x64\xed\x16\x06\x12"
        "\x20\x99\x55\x21\x7b\x10\xef\x57\x8b\xbf\x2e\x09\xee\x6b\xaa\x7c"
        "\xcc\x3c\x95\xee\xba\xd7\x4b\x88\x84\x88\xd2\x70\x4c\x09\x30\xf2"
        "\xaf\xb0\x99\x0d\x1f\x5f\xa7\xc5\xaf\x61\xc1\x18\xed\x16\xb0\x32"
        "\xf5\x07\x2f\x72\xb1\x23\x66\x1f\xf5\x18\xef\xb3\x9d\xf0\x4a\x02"
        "\x8f\x37\xff\xb0\xd7\xaf\xd3\x09\xb4\x4a\x2c\x63\xa3\x24\x1e\x52"
        "\xdf\x12\x9c\x8e\xff\x31\x2f\x0e\x48\xfa\x25\xc5\x43\xe4\x71\x69"
        "\xf4\x84\x91\x84\x0c\xc2\x3f\x7d\xb0\xe1\xe6\x03\x36\xbb\xed\x22"
        "\x89\xe9\x81\x6c\x4e\xfb\x41\x84\xba\xf1\x5b\x1e\xbf\x30\xbf\x77"
        "\x0e\x47\x1c\x84\xe9\xa0\x9e\x5b\x35\xa7\xee\x3c\x40\x0d\xb9\x70"
        "\x2a\x11\xf8\xc9\x41\x33\x89\x9c\x51\xf2\x40\xf0\xe5\xe8\xd7\x1e"
        "\x77\xde\x19\x46\x00\x57\xf0\x02\x5c\x1d\x64\xb9\x40\xc8\x1a\x99"
        "\x5f\xa7\x4d\x5a\x72\x3e\x80\xc3\xa1\x1a\x6e\x1e\xd0\x79\x06\x6b"
        "\xee\x50\x76\x81\x71\xa4\xb1\xdb\xab\x40\x1a\xa7\x8a\xee\x06\xb9"
        "\xf2\x22\x13\x30\x43\x19\xe1\xe3\x34\xce\x1e\x03\x1a\x04\xe7\xa4"
        "\x4a\xc7\x6a\x8e\x6f\xad\x7f\x3d\x89\x11\x97\xad\x95\x20\xe8\x35"
        "\xc7\xd1\x02\x00\x0a\xe5\x81\x25\x91\x2c\xa2\x87\x16\xc3\xcc\xc9"
        "\x1f\x6d\x56\x64\x82\xd6\x69\x97\x7d\xcb\x58\x40\xd0\x00\x16\xc3"
        "\xee\xb7\x19\xd6\x06\x6f\x39\x7b\x60\xba\x7b\xef\xfb\xc0\x79\x3c"
        "\xe7\x0b\x6f\x67\x36\xaf\xa9\x3a\x3f\xc2\x31\x72\x09\xa3\xfd\x4e"
        "\xc8\x52\x96\xda\x67\xf1\xb9\x79\xa9\xcc\xd3\x6f\xe7\xf6\xa0\x80"
        "\x0f\xcf\x7c\xb5\x9a\x89\xe6\xfa\xd3\xec\xc9\xf5\xcc\x53\x65\x73"
        "\x05\xd3\xd7\x83\x56\x84\x68\x94\xa3\x52\x1a\x0a\xcb\xe7\xcf\xed"
        "\x22\xfe\xd6\x3c\xf7\x84\x03\xbf\xeb\x77\x82\x5b\x8a\x35\x67\x2b"
        "\x97\x75\x5a\x81\xc9\x37\x6b\xe3\x77\x4f\x82\x5c\x75\x3f\xc3\xa1"
        "\x84\xe4\x2c\x43\x33\x8b\xec\xd6\x32\xf2\xfa\x3a\x65\x06\xb7\x51"
        "\x88\x85\x5b\xab\x0f\x36\x41\xc5\x2f\x6d\x34\x31\x70\x59\xb5\x2e"
        "\x44\x31\x62\xb9\x38\x39\xf7\xb6\x6e\xcf\xf2\x7f\x78\xdd\xf0\x8e"
        "\xc4\x23\x5a\x48\xd0\xa5\xa8\x90\x69\xa9\x53\xec\x45\xd6\x97\x9b"
        "\x92\x3e\x0a\x50\x90\x3f\xe9\x92\xdc\x85\xaa\xab\x57\xa7\x0e\xe8"
        "\xff\xcf\xfc\x4d\x9a\xc6\x36\xe3\x5a\x0d\x83\x12\xc5\x84\x85\x8a"
        "\x74\xcf\x42\x33\x8c\xeb\xd3\x49\x4d\x60\x15\xbe\xad\x73\x92\x37"
        "\x29\x3e\x63\x83\x1f\xd1\xc6\x9a\xbc\xb8\xc6\xac\x34\x34\x87\xd2"
        "\xe7\x0b\x77\xf9\x2f\x52\x37\xbb\x10\xa8\xe1\xde\x33\xf2\x52\x2e"
        "\xe5\x56\x7e\xff\x5c\xec\x82\x50\xe1\xb0\x4e\xa1\x23\x86\x08\x22"
        "\xa6\x56\x2b\x40\x99\xf4\x8e\x3d\xe2\x10\x05\xf1\xdd\x21\x69\x77"
        "\x07\x59\x90\x2f\xf1\xbb\xb8\x03\x5a\x21\xe1\xe5\x0c\xaa\x52\xda"
        "\xa1\x73\x31\x18\x12\xb2\x85\x52\x07\xf6\x8f\x23\xb0\xf7\x4a\x9a"
        "\x6f\x0a\x6c\x1f\xbe\x3f\x88\xad\xe9\x55\x4a\xb7\x44\xfb\xf8\x25"
        "\x6a\x2a\xf1\xd9\xfe\xb8\x62\xc5\xae\xed\x5c\x8b\x0f\x4b\x8a\xfe"
        "\x01\x68\x8b\xe1\x3f\x84\x3c\x6f\x10\xbf\xb5\x0f\x82\x41\x97\x39"
        "\x64\x18\x3d\xef\xa4\x3a\x5f\x33\x9d\x4b\x6e\xa3\x77\x97\x06\xfb"
        "\x1b\x8f\xf0\xed\xe3\x84\x1b\x73\x51\x72\x0b\x2d\xf1\x78\x59\xd9"
        "\x16\x50\x97\x1b\xe0\x5d\x27\xc3\xbb\x77\x2e\x15\xd2\xd2\x33\x68"
        "\xee\xd8\x0f\x28\xf5\x0c\x1b\x98\x1b\xda\x1d\x75\xc4\x2b\xb8\x45"
        "\x8b\xc0\x6e\x88\x88\xad\x61\xf8\x09\x1c\xb1\x46\xeb\xbb\xa2\xf5"
        "\xbc\x5c\x7b\x02\xdb\xcc\xad\x97\x1c\x5b\xa9\x97\x0e\x49\xea\x6d"
        "\x13\xba\x6f\x11\xcf\x2c\x2f\xc7\x9b\xb4\x80\x49\x18\x9e\x4c\x94"
        "\x5a\x55\x06\x4d\x42\x75\xb6\xa2\x61\xdb\xfa\x41\xca\x92\x70\xcc"
        "\x7e\x52\x66\x01\x13\x53\xef\xae\x40\xbd\xb7\xb6\xf2\xc7\xdd\x28"
        "\xb1\x11\xd4\x78\x79\xc2\x22\xbf\x29\xa0\x3a\x83\xc5\x76\x17\xe6"
        "\x94\x1e\xee\x63\xd2\x1e\x52\xfd\x24\x9f\x40\xa7\x0c\x0a\xe7\xeb"
        "\x9d\x12\x2a\xf3\xe3\x5f\x70\xe9\x31\x51\x6f\xe2\xac\xe7\xfc\xf2"
        "\x23\xe4\x6d\xe3\x85\xe3\xb8\x4c\x7f\xa1\x2c\x8c\xd7\xbb\x34\x70"
        "\x12\x7b\x6c\xe7\x8b\x4d\xb5\xdf\x52\xbb\x48\x5a\x21\x81\x16\x62"
        "\xdd\x8a\xbf\xa7\xe3\x12\x02\x52\x30\x6e\x7d\x76\x52\x1d\x43\x71"
        "\xf3\x6b\x1c\xa0\xd3\xd8\x59\xb0\x2d\xb9\x66\x9a\xb5\x00\xd9\xa6"
        "\xeb\x3f\x8a\x26\x90\x98\xb3\x69\x5f\x9f\x85\x53\x28\x3c\x9e\xce"
        "\x93\x7e\xab\x17\x76\x3d\x67\x0c\x4e\x21\x46\x3c\x94\x53\xba\xdc"
        "\xdf\x2a\x87\x09\x24\x76\x38\x39\x2e\xc0\x58\x1f\x99\x1a\xee\x9a"
        "\xaf\xc4\xc4\x3e\xfc\xeb\x4c\xfa\x5f\x43\x4f\x97\xe9\xac\xa9\x03"
        "\x29\x0e\x64\xeb\x24\x27\x87\xe3\xf2\xc3\xc6\x5d\xde\xe5\x3f\x46"
        "\xba\xd9\x75\x31\xda\x9c\xb2\xfd\x2b\xa5\x7e\x78\x3a\xaf\x22\xc4"
        "\x80\x90\x31\xf4\xd5\x9b\x04\x19\x09\xa2\x26\x91\xd2\xfe\x44\xb6";

// XOR transform utility function (same for read or write)

inline void XformData(void *dataIn, void *dataOut, UInt32 len, UInt64 pos)
{
    UInt32 xorSize = sizeof(quakeliveXor) - 1;
    UInt32 dataIndex, xorIndex;
    for (dataIndex = 0; dataIndex < len; dataIndex++)
    {
        xorIndex = (pos + dataIndex) % xorSize;
        ((Byte*)dataOut)[dataIndex] =
            ((Byte*)dataIn)[dataIndex] ^ quakeliveXor[xorIndex];
    }
}

// Constructor for CPk3InStream

CPk3InStream::CPk3InStream(IInStream *stream)
{
    _stream = stream;  
    // XXX This constructor should only be invoked when starting at the
    //     beginning of the pk3 archive, but I still need to think about
    //     whether the stream position would ever NOT be zero at this point.
    //     Test cases of pk3-inside-other-archive perhaps? If the stream can
    //     have a nonzero seek pointer, then the initial pointer would need
    //     to be saved & used to affect the XOR.
    _pos = 0;
}

// INTERFACE_IInStream for CPk3InStream

STDMETHODIMP CPk3InStream::Read(void *data, UInt32 size, UInt32 *processedSize)
{
    UInt32 realProcessedSize;
    HRESULT result = _stream->Read(data, size, &realProcessedSize);
    // The data read from the stream is XOR-scrambled, so unscramble it before
    // returning it to the caller.
    XformData(data, data, realProcessedSize, _pos);
    _pos += realProcessedSize;
    if (processedSize != NULL)
    {
        *processedSize = realProcessedSize;
    }
    return result;
}

STDMETHODIMP CPk3InStream::Seek(Int64 offset, UInt32 seekOrigin, UInt64 *newPosition)
{
    HRESULT result = _stream->Seek(offset, seekOrigin, &_pos);
    if (newPosition != NULL)
    {
        *newPosition = _pos;
    }
    return result;
}

// Constructor for CPk3OutStream

CPk3OutStream::CPk3OutStream(IOutStream *stream)
{
    _stream = stream;  
    // XXX Similar to CPk3InStream, question about whether seek pointer is
    //     always zero at this point.
    _pos = 0;
}

// INTERFACE_IOutStream for CPk3OutStream

STDMETHODIMP CPk3OutStream::Write(const void *data, UInt32 size, UInt32 *processedSize)
{
    // We need to XOR-scramble the data before writing it to the stream. To be
    // polite we shouldn't mess with the input data buffer -- especially since
    // we might do a partial write. So we'll stage the scrambled data into our
    // own buffer and write that to the stream in staging-buffer-sized chunks.
    HRESULT result = S_OK;
    UInt32 sizeLeft = size;
    while (result == S_OK && sizeLeft != 0)
    {
        UInt32 len;
        if (sizeLeft > STAGING_BUFFER_SIZE)
        {
            len = STAGING_BUFFER_SIZE;
        }
        else
        {
            len = sizeLeft;
        }
        XformData(&(((Byte*)data)[size - sizeLeft]), _staging, len, _pos);
        UInt32 realProcessedSize;
        result = _stream->Write(_staging, len, &realProcessedSize);
        // N.B. It does look like we're doing some redundant math here, but
        // this is a way to avoid cramming 64-bit values into 32-bit function
        // parameters. (We could do 64-to-32 bit conversions that are "known
        // to be safe" because of the overall algorithm, but it's hard to
        // convince the compiler about that safety & it feels like it's trying
        // too hard to be clever.)
        _pos += realProcessedSize;
        sizeLeft -= realProcessedSize;
    }
    if (processedSize != NULL) {
        *processedSize = size - sizeLeft;
    }
    return result;
}

STDMETHODIMP CPk3OutStream::Seek(Int64 offset, UInt32 seekOrigin, UInt64 *newPosition)
{
    HRESULT result = _stream->Seek(offset, seekOrigin, &_pos);
    if (newPosition != NULL)
    {
        *newPosition = _pos;
    }
    return result;
}

STDMETHODIMP CPk3OutStream::SetSize(UInt64 newSize)
{
    // This should not affect the seek pointer.
    return _stream->SetSize(newSize);
}
