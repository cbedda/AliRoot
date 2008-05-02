#ifndef AliHLTMUONDECISIONCOMPONENT_H
#define AliHLTMUONDECISIONCOMPONENT_H
/* This file is property of and copyright by the ALICE HLT Project        *
 * ALICE Experiment at CERN, All rights reserved.                         *
 * See cxx source for full Copyright notice                               */

/* $Id: $ */

///
///  @file   AliHLTMUONDecisionComponent.h
///  @author Artur Szostak <artursz@iafrica.com>
///  @date   30 April 2008
///  @brief  Declares the decision component for dimuon HLT triggering.
///

#include "AliHLTProcessor.h"
#include "AliHLTMUONDataTypes.h"
#include <vector>

#if __GNUC__ && __GNUC__ < 3
#define std
#endif

extern "C" struct AliHLTMUONMansoTrackStruct;
extern "C" struct AliHLTMUONTrackDecisionStruct;
extern "C" struct AliHLTMUONPairDecisionStruct;
extern "C" struct AliHLTMUONSinglesDecisionBlockStruct;
extern "C" struct AliHLTMUONPairsDecisionBlockStruct;


/**
 * @class AliHLTMUONDecisionComponent
 * @brief Dimuon HLT trigger decision component.
 *
 * This class implements the dimuon HLT trigger decision component.
 * The dimuon trigger decision is generated by first applying two pT cuts to the
 * single tracks: a low cut for the J/psi family and a high cut for the upsilon
 * family. From the tracks that pass the cuts, we count them and build up some
 * statistics like the number of tracks passing the low or high pT cut.
 * The algorithm then looks at pairs of tracks and similarly counts the number
 * like sign or unlike sign pairs where both tracks passed the low or high pT cut
 * or pairs that did not pass any cuts.
 * At this point the invariant mass of the pairs is calculated and two mass cuts
 * are applied. The number of pairs that pass the low or high mass cut are then
 * counted. The results are encoded into two data blocks, one for trigger decisions
 * for single tracks and another for the track pairs.
 */
class AliHLTMUONDecisionComponent : public AliHLTProcessor
{
public:
	AliHLTMUONDecisionComponent();
	virtual ~AliHLTMUONDecisionComponent();

	// Public functions to implement the AliHLTProcessor interface.
	// These functions are required for the registration process.
	virtual const char* GetComponentID();
	virtual void GetInputDataTypes(AliHLTComponentDataTypeList& list);
	virtual AliHLTComponentDataType GetOutputDataType();
	virtual int GetOutputDataTypes(AliHLTComponentDataTypeList& list);
	virtual void GetOutputDataSize(unsigned long& constBase, double& inputMultiplier);
	virtual AliHLTComponent* Spawn();

protected:

	// Protected functions to implement the AliHLTProcessor interface.
	// These functions provide initialization as well as the actual processing
	// capabilities of the component.
	virtual int DoInit(int argc, const char** argv);
	virtual int DoDeinit();
	virtual int Reconfigure(const char* cdbEntry, const char* componentId);
	virtual int DoEvent(
			const AliHLTComponentEventData& evtData,
			const AliHLTComponentBlockData* blocks,
			AliHLTComponentTriggerData& trigData,
			AliHLTUInt8_t* outputPtr,
			AliHLTUInt32_t& size,
			std::vector<AliHLTComponentBlockData>& outputBlocks
		);
	
	using AliHLTProcessor::DoEvent;

private:

	// Do not allow copying of this class.
	AliHLTMUONDecisionComponent(const AliHLTMUONDecisionComponent& /*obj*/);
	AliHLTMUONDecisionComponent& operator = (const AliHLTMUONDecisionComponent& /*obj*/);
	
	/**
	 * Reads the cut parameters from the CDB.
	 * \param path  The relative CDB path to use for the CDB entry.
	 *              If NULL the default value is used.
	 * \param setLowPtCut  Indicates if the low pT cut should be set (default true).
	 * \param setHighPtCut  Indicates if the high pT cut should be set (default true).
	 * \param setLowMassCut  Indicates if the low invariant mass cut should be set (default true).
	 * \param setHighMassCut  Indicates if the high invariant mass cut should be set (default true).
	 * \return 0 is returned on success and a non-zero value to indicate failure.
	 */
	int ReadConfigFromCDB(
			const char* path = NULL,
			bool setLowPtCut = true, bool setHighPtCut = true,
			bool setLowMassCut = true, bool setHighMassCut = true
		);
	
	int AddTrack(const AliHLTMUONMansoTrackStruct* track);
	
	void ApplyTriggerAlgorithm(
			AliHLTMUONSinglesDecisionBlockStruct& singlesHeader,
			AliHLTMUONTrackDecisionStruct* singlesDecision,
			AliHLTMUONPairsDecisionBlockStruct& pairsHeader,
			AliHLTMUONPairDecisionStruct* pairsDecision
		);

	AliHLTUInt32_t fMaxTracks; /// The maximum number of elements that can be stored in fTracks.
	AliHLTUInt32_t fTrackCount;  /// The current number of elements stored in fTracks.
	const AliHLTMUONMansoTrackStruct** fTracks;  /// Pointers to the track structures in input data blocks.
	AliHLTFloat32_t fLowPtCut;  /// The low pT cut value to apply to tracks. [GeV/c]
	AliHLTFloat32_t fHighPtCut;  /// The high pT cut value to apply to tracks. [GeV/c]
	AliHLTFloat32_t fLowMassCut;  /// The low invariant mass cut value to apply to tracks. [GeV/c^2]
	AliHLTFloat32_t fHighMassCut;  /// The high invariant mass cut value to apply to tracks. [GeV/c^2]
	bool fWarnForUnexpecedBlock;  /// Flag indicating if we should log a warning if we got a block of an unexpected type.
	
	ClassDef(AliHLTMUONDecisionComponent, 0);  // Trigger decision component for the dimuon HLT.
};

#endif // AliHLTMUONDECISIONCOMPONENT_H
