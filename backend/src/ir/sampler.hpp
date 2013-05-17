/*
 * Copyright © 2012 Intel Corporation
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * \file sampler.hpp
 *
 * \author Benjamin Segovia <benjamin.segovia@intel.com>
 */
#ifndef __GBE_IR_SAMPLER_HPP__
#define __GBE_IR_SAMPLER_HPP__

#include "ir/register.hpp"
#include "sys/map.hpp"

namespace gbe {
namespace ir {

  /*! A sampler set is a set of global samplers which are defined as constant global
   * sampler or defined in the outermost kernel scope variables. According to the spec
   * all the variable should have a initialized integer value and can't be modified.
   */
  class Context;

  struct SamplerRegSlot {
    Register reg;
    uint32_t slot;
  };

  class SamplerSet
  {
  public:
    /*! Append the specified sampler and return the allocated offset.
     *  If the speficied sampler is exist, only return the previous offset and
     *  don't append it again. Return -1, if failed.*/
    Register append(uint32_t clkSamplerValue, Context *ctx);
    /*! Append a sampler defined in kernel args. */
    void append(Register samplerArg, Context *ctx);
    /*! Get the sampler idx (actual location) */
    const uint32_t getIdx(const Register reg) const;
    size_t getDataSize(void) { return samplerMap.size(); }
    size_t getDataSize(void) const { return samplerMap.size(); }
    void getData(uint32_t *samplers) const {
      for(auto &it : samplerMap)
        samplers[it.second.slot] = it.first;
    }

    void operator = (const SamplerSet& other) {
      regMap.insert(other.regMap.begin(), other.regMap.end());
      samplerMap.insert(other.samplerMap.begin(), other.samplerMap.end());
    }

    SamplerSet(const SamplerSet& other) : samplerMap(other.samplerMap.begin(), other.samplerMap.end()) { }
    SamplerSet() {}
  private:
    void appendReg(const Register reg, uint32_t key, Context *ctx);
    map<uint32_t, SamplerRegSlot> samplerMap;
    map<Register, SamplerRegSlot> regMap;
    GBE_CLASS(SamplerSet);
  };
} /* namespace ir */
} /* namespace gbe */

#endif /* __GBE_IR_SAMPLER_HPP__ */