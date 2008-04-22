#ifndef _ALIHLTTPCTRACKLETFORMAT_HPP_
#define _ALIHLTTPCTRACKLETFORMAT_HPP_

//* This file is property of and copyright by the ALICE HLT Project        * 
//* ALICE Experiment at CERN, All rights reserved.                         *
//* See cxx source for full Copyright notice                               *

#include "AliHLTDataTypes.h"
#include "AliHLTTPCTrackSegmentData.h"

/**
 * @struct AliHLTTPCTrackletData
 * Primitive data exchange structure for TPC tracks.
 *
 * @ingroup alihlt_tpc_datastructs
 */
struct AliHLTTPCTrackletData
    {
	AliHLTUInt32_t fTrackletCnt;
#ifndef __SUNPRO_CC
	AliHLTTPCTrackSegmentData fTracklets[];
#else
	AliHLTTPCTrackSegmentData fTracklets[1];
#endif
	//AliHLTTPCSpacePointData fSpacePoints[];
    };


#endif // _ALIHLTTPCTRACKLETFORMAT_HPP_
