/****
 * Sming Framework Project - Open Source framework for high efficiency native ESP8266 development.
 * Created 2015 by Skurydin Alexey
 * http://github.com/anakod/Sming
 * All files of the Sming Core are provided under the LGPL v3 license.
 ****/

#ifndef _SMING_CORE_DATA_MEMORY_DATA_STREAM_H_
#define _SMING_CORE_DATA_MEMORY_DATA_STREAM_H_

#include "ReadWriteStream.h"

/** @addtogroup stream
 *  @{
 */

/*
 * MemoryDataStream
 *
 * This is intended to allow data to be streamed into it, then streamed back out at a later
 * date.
 *
 * It is _not_ intended to have data continuously written in and read out; memory is not reclaimed
 * as it is read.
 */
class MemoryDataStream : public ReadWriteStream
{
public:
	/** @brief Memory data stream base class
    */
	MemoryDataStream()
	{
	}

	virtual ~MemoryDataStream()
	{
		free(buf);
	}

	//Use base class documentation
	virtual StreamType getStreamType() const
	{
		return eSST_Memory;
	}

	/** @brief  Get a pointer to the current position
	 *  @retval "const char*" Pointer to current cursor position within the data stream
	 */
	const char* getStreamPointer() const
	{
		return pos;
	}

	/**
	 * @brief Return the total length of the stream
	 * @retval int -1 is returned when the size cannot be determined
	*/
	int available()
	{
		return size - (pos - buf);
	}

	using ReadWriteStream::write;

	/** @brief  Write chars to end of stream
     *  @param  buffer Pointer to buffer to write to the stream
     *  @param  size Quantity of chars to write
     *  @retval size_t Quantity of chars written to stream
     */
	virtual size_t write(const uint8_t* buffer, size_t size);

	//Use base class documentation
	virtual uint16_t readMemoryBlock(char* data, int bufSize);

	//Use base class documentation
	virtual bool seek(int len);

	//Use base class documentation
	virtual bool isFinished()
	{
		return size == (pos - buf);
	}

private:
	char* buf = nullptr;
	char* pos = nullptr;
	int size = 0;
	int capacity = 0;
};

/** @} */
#endif /* _SMING_CORE_DATA_MEMORY_DATA_STREAM_H_ */
