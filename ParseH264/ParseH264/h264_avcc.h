#pragma once

#include <stdint.h>
#include <assert.h>
#include "bs.h"
#include "h264_stream.h"

#ifdef _cplusplus
extern "C" {
#endif

	typedef struct  
	{
		int configurationVersion;
		int AVCProfileIndication;
		int profile_compatibility;
		int AVCLevelIndication;
		int lengthSizeMinusOne;
		int numOfSequenceParameterSets;
		sps_t** sps_table;
		int numOfPictureParameterSets;
		pps_t** pps_table;
	}avcc_t;

	avcc_t* avcc_new();
	void avcc_free(avcc_t* avcc);
	int read_avcc(avcc_t* avcc, h264_stream_t* h, bs_t* b);
	int write_avcc(avcc_t* avcc, h264_stream_t* h, bs_t* b);
	void debug_avcc(avcc_t* avcc);


#ifdef _cplusplus
}
#endif