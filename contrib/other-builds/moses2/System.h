/*
 * System.h
 *
 *  Created on: 23 Oct 2015
 *      Author: hieu
 */

#pragma once
#include <vector>
#include <deque>
#include <boost/thread/tss.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/shared_ptr.hpp>
#include "FF/FeatureFunctions.h"
#include "Weights.h"
#include "MemPool.h"
#include "Recycler.h"
#include "legacy/FactorCollection.h"
#include "legacy/Parameter.h"
#include "TypeDef.h"
#include "legacy/Bitmaps.h"
#include "legacy/OutputCollector.h"
#include "parameters/AllOptions.h"

namespace Moses2
{
namespace NSCubePruning
{
class Stack;
}

class FeatureFunction;
class StatefulFeatureFunction;
class PhraseTable;
class HypothesisBase;

class System
{
public:
  const Parameter &params;
  AllOptions options;
  FeatureFunctions featureFunctions;
  Weights weights;
  std::vector<const PhraseTable*> mappings;

  mutable boost::shared_ptr<OutputCollector> bestCollector, nbestCollector;

  // moses.ini params
  int cpuAffinityOffset;
  int cpuAffinityOffsetIncr;

  // server
  int port;              // this is for the abyss server
  std::string logfile;   // this is for the abyss server
  int maxConn;           // this is for the abyss server
  int maxConnBacklog;    // this is for the abyss server
  int keepaliveTimeout;  // this is for the abyss server
  int keepaliveMaxConn;  // this is for the abyss server
  int timeout;           // this is for the abyss server
  bool is_serial;

  System(const Parameter &paramsArg);
  virtual ~System();

  MemPool &GetSystemPool() const;
  MemPool &GetManagerPool() const;
  FactorCollection &GetVocab() const;

  Recycler<HypothesisBase*> &GetHypoRecycler() const;

protected:
  mutable FactorCollection m_vocab;
  mutable boost::thread_specific_ptr<MemPool> m_managerPool;
  mutable boost::thread_specific_ptr<MemPool> m_systemPool;

  mutable boost::thread_specific_ptr<Recycler<HypothesisBase*> > m_hypoRecycler;

  void LoadWeights();
  void LoadMappings();
};

}

