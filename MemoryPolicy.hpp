/**
 * ****************************************************************************
 * Copyright (c) 2015, Robert Lukierski.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * ****************************************************************************
 * Memory Policies.
 * ****************************************************************************
 */

#ifndef CORE_MEMORY_POLICY_HPP
#define CORE_MEMORY_POLICY_HPP

namespace core
{
template<typename TargetFrom, typename TargetTo>
struct TargetTransfer { };
}

#include <MemoryPolicyHost.hpp>
#ifdef CORE_HAVE_CUDA
#include <MemoryPolicyCUDA.hpp>
#endif // CORE_HAVE_CUDA

#ifdef CORE_HAVE_OPENCL
#include <MemoryPolicyOpenCL.hpp>
#endif // CORE_HAVE_OPENCL

namespace core
{
#if 0
template<template<typename> class Target> struct TargetTraits { };

template<typename ElementT>
template<> struct TargetTraits<TargetHost<ElementT>>
{
    static const bool IsDeviceCUDA = false;
    static const bool IsDeviceOpenCL = false;
    static const bool IsHost = true;
};    

#ifdef CORE_HAVE_CUDA
template<typename ElementT>
template<> struct TargetTraits<TargetDeviceCUDA<ElementT>>
{
    static const bool IsDeviceCUDA = true;
    static const bool IsDeviceOpenCL = false;
    static const bool IsHost = false;
};
#endif // CORE_HAVE_CUDA
        
#ifdef CORE_HAVE_OPENCL
template<typename ElementT>
template<> struct TargetTraits<TargetDeviceOpenCL<ElementT>>
{
    static const bool IsDeviceCUDA = false;
    static const bool IsDeviceOpenCL = true;
    static const bool IsHost = false;
};   
#endif // CORE_HAVE_OPENCL
#endif
}

#endif // CORE_MEMORY_POLICY_HPP
