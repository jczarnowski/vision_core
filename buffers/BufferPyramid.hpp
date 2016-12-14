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
 * 2D Host/Device Buffer Pyramids.
 * ****************************************************************************
 */

#ifndef CORE_BUFFER_PYRAMID_HPP
#define CORE_BUFFER_PYRAMID_HPP

#include <buffers/PyramidBase.hpp>
#include <buffers/Buffer2D.hpp>

namespace core
{

template<typename T, std::size_t Levels, template<typename = T> class Target = TargetHost>
class BufferPyramidView { };

/**
 * Buffer Pyramid View - Host.
 */
template<typename T, std::size_t Levels>
class BufferPyramidView<T,Levels,TargetHost> : public PyramidViewBase<Buffer2DView, T,Levels,TargetHost>
{
public:
    typedef PyramidViewBase<Buffer2DView, T,Levels,TargetHost> BaseT;
    typedef typename BaseT::ViewType LevelT;
    static const std::size_t LevelCount = BaseT::LevelCount;
    
    EIGEN_DEVICE_FUNC inline BufferPyramidView() { }
    
    EIGEN_DEVICE_FUNC inline ~BufferPyramidView() { }
    
    EIGEN_DEVICE_FUNC inline BufferPyramidView(const BufferPyramidView<T,LevelCount,TargetHost>& pyramid) : BaseT(pyramid) { }
    
    EIGEN_DEVICE_FUNC inline BufferPyramidView(BufferPyramidView<T,LevelCount,TargetHost>&& pyramid) : BaseT(std::move(pyramid)) { }
    
    EIGEN_DEVICE_FUNC inline BufferPyramidView<T,LevelCount,TargetHost>& operator=(const BufferPyramidView<T,LevelCount,TargetHost>& pyramid)
    {
        BaseT::operator=(pyramid);
        return *this;
    }
    
    EIGEN_DEVICE_FUNC inline BufferPyramidView<T,LevelCount,TargetHost>& operator=(BufferPyramidView<T,LevelCount,TargetHost>&& pyramid)
    {
        BaseT::operator=(std::move(pyramid));
        return *this;
    }
    
    inline void memset(unsigned char v = 0)
    {
        for(std::size_t l = 0 ; l < LevelCount ; ++l) 
        {
            BaseT::imgs[l].memset(v);
        }
    }
    
    inline void copyFrom(const BufferPyramidView<T,Levels,TargetHost>& pyramid)
    {
        for(std::size_t l = 0 ; l < LevelCount ; ++l) 
        {
            BaseT::imgs[l].copyFrom(pyramid.imgs[l]);
        }
    }
    
#ifdef CORE_HAVE_CUDA
    inline void copyFrom(const BufferPyramidView<T,Levels,TargetDeviceCUDA>& pyramid)
    {
        for(std::size_t l = 0 ; l < LevelCount ; ++l) 
        {
            BaseT::imgs[l].copyFrom(pyramid.imgs[l]);
        }
    }
#endif // CORE_HAVE_CUDA

#ifdef CORE_HAVE_OPENCL
    inline void copyFrom(const cl::CommandQueue& queue, const BufferPyramidView<T,Levels,TargetDeviceOpenCL>& pyramid)
    {
        for(std::size_t l = 0 ; l < LevelCount ; ++l) 
        {
            BaseT::imgs[l].copyFrom(queue, pyramid.imgs[l]);
        }
    }
#endif // CORE_HAVE_OPENCL
};

#ifdef CORE_HAVE_CUDA

/**
 * Buffer Pyramid View - CUDA.
 */
template<typename T, std::size_t Levels>
class BufferPyramidView<T,Levels,TargetDeviceCUDA> : public PyramidViewBase<Buffer2DView, T,Levels,TargetDeviceCUDA>
{
public:
    typedef PyramidViewBase<Buffer2DView, T,Levels,TargetDeviceCUDA> BaseT;
    typedef typename BaseT::ViewType LevelT;
    static const std::size_t LevelCount = BaseT::LevelCount;
    
    EIGEN_DEVICE_FUNC inline BufferPyramidView() { }
    
    EIGEN_DEVICE_FUNC inline ~BufferPyramidView() { }
    
    EIGEN_DEVICE_FUNC inline BufferPyramidView(const BufferPyramidView<T,LevelCount,TargetDeviceCUDA>& pyramid) : BaseT(pyramid) { }
    
    EIGEN_DEVICE_FUNC inline BufferPyramidView(BufferPyramidView<T,LevelCount,TargetDeviceCUDA>&& pyramid) : BaseT(std::move(pyramid)) { }
    
    EIGEN_DEVICE_FUNC inline BufferPyramidView<T,LevelCount,TargetDeviceCUDA>& operator=(const BufferPyramidView<T,LevelCount,TargetDeviceCUDA>& pyramid)
    {
        BaseT::operator=(pyramid);
        return *this;
    }
    
    EIGEN_DEVICE_FUNC inline BufferPyramidView<T,LevelCount,TargetDeviceCUDA>& operator=(BufferPyramidView<T,LevelCount,TargetDeviceCUDA>&& pyramid)
    {
        BaseT::operator=(std::move(pyramid));
        return *this;
    }
    
    inline void memset(unsigned char v = 0)
    {
        for(std::size_t l = 0 ; l < LevelCount ; ++l) 
        {
            BaseT::imgs[l].memset(v);
        }
    }
    
    template<template<typename = T> class TargetFrom>
    inline void copyFrom(const BufferPyramidView<T,Levels,TargetFrom>& pyramid)
    {
        for(std::size_t l = 0 ; l < LevelCount ; ++l) 
        {
            BaseT::imgs[l].copyFrom(pyramid.imgs[l]);
        }
    }
};

#endif // CORE_HAVE_CUDA

#ifdef CORE_HAVE_OPENCL
/**
 * Buffer Pyramid View - OpenCL.
 */
template<typename T, std::size_t Levels>
class BufferPyramidView<T,Levels,TargetDeviceOpenCL> : public PyramidViewBase<Buffer2DView, T,Levels,TargetDeviceOpenCL>
{
public:
    typedef PyramidViewBase<Buffer2DView, T,Levels,TargetDeviceOpenCL> BaseT;
    typedef typename BaseT::ViewType LevelT;
    static const std::size_t LevelCount = BaseT::LevelCount;
    
    inline BufferPyramidView() { }
    
    inline ~BufferPyramidView() { }
    
    inline BufferPyramidView(const BufferPyramidView<T,LevelCount,TargetDeviceOpenCL>& pyramid) : BaseT(pyramid) { }
    
    inline BufferPyramidView(BufferPyramidView<T,LevelCount,TargetDeviceOpenCL>&& pyramid) : BaseT(std::move(pyramid)) { }
    
    inline BufferPyramidView<T,LevelCount,TargetDeviceOpenCL>& operator=(const BufferPyramidView<T,LevelCount,TargetDeviceOpenCL>& pyramid)
    {
        BaseT::operator=(pyramid);
        return *this;
    }
    
    inline BufferPyramidView<T,LevelCount,TargetDeviceOpenCL>& operator=(BufferPyramidView<T,LevelCount,TargetDeviceOpenCL>&& pyramid)
    {
        BaseT::operator=(std::move(pyramid));
        return *this;
    }
    
    inline void memset(unsigned char v = 0)
    {
        for(std::size_t l = 0 ; l < LevelCount ; ++l) 
        {
            BaseT::imgs[l].memset(v);
        }
    }
    
    inline void copyFrom(const cl::CommandQueue& queue, const BufferPyramidView<T,Levels,TargetHost>& pyramid)
    {
        for(std::size_t l = 0 ; l < LevelCount ; ++l) 
        {
            BaseT::imgs[l].copyFrom(queue, pyramid.imgs[l]);
        }
    }
    
    inline void copyFrom(const cl::CommandQueue& queue, const BufferPyramidView<T,Levels,TargetDeviceOpenCL>& pyramid)
    {
        for(std::size_t l = 0 ; l < LevelCount ; ++l) 
        {
            BaseT::imgs[l].copyFrom(queue, pyramid.imgs[l]);
        }
    }

    inline void memset(const cl::CommandQueue& queue, cl_float4 v)
    {
        for(std::size_t l = 0 ; l < LevelCount ; ++l) 
        {
            BaseT::imgs[l].memset(queue, v);
        }
    }
};

#endif //  CORE_HAVE_OPENCL

/// ***********************************************************************

/**
 * CUDA/Host Buffer Pyramid Creation.
 */
template<typename T, std::size_t Levels, template<typename = T> class Target = TargetHost>
class BufferPyramidManaged : public BufferPyramidView<T, Levels, Target>
{
public:
    typedef BufferPyramidView<T, Levels, Target> ViewT;
    typedef typename ViewT::ViewType LevelT;
    static const std::size_t LevelCount = Levels;
        
    BufferPyramidManaged() = delete;
    
    inline BufferPyramidManaged(std::size_t w, std::size_t h)
    {        
        // Build power of two structure
        for(std::size_t l = 0; l < LevelCount && (w>>l > 0) && (h>>l > 0); ++l ) 
        {
            typename Target<T>::PointerType ptr = 0;
            std::size_t line_pitch = 0;
            
            Target<T>::AllocatePitchedMem(&ptr, &line_pitch, w >> l, h >> l);
            
            ViewT::imgs[l] = core::Buffer2DView<T,Target>((T*)ptr, w >> l, h >> l, line_pitch);
        }
    }
    
    BufferPyramidManaged(const BufferPyramidManaged<T,LevelCount,Target>& img) = delete;
    
    inline BufferPyramidManaged(BufferPyramidManaged<T,LevelCount,Target>&& img) : ViewT(std::move(img))
    {
        
    }
    
    BufferPyramidManaged<T,LevelCount,Target>& operator=(const BufferPyramidManaged<T,LevelCount,Target>& img) = delete;
    
    inline BufferPyramidManaged<T,LevelCount,Target>& operator=(BufferPyramidManaged<T,LevelCount,Target>&& img)
    {
        ViewT::operator=(std::move(img));
        return *this;
    }
    
    inline ~BufferPyramidManaged()
    {
        for(std::size_t l = 0; l < LevelCount ; ++l)
        {
            Target<T>::DeallocatePitchedMem(ViewT::imgs[l].ptr());
        }
    }
    
    inline const ViewT& view() const { return (const ViewT&)*this; }
    inline ViewT& view() { return (ViewT&)*this; }
};

#ifdef CORE_HAVE_OPENCL

/**
 * OpenCL Buffer Pyramid Creation.
 */
template<typename T, std::size_t Levels>
class BufferPyramidManaged<T,Levels,TargetDeviceOpenCL> : public BufferPyramidView<T, Levels, TargetDeviceOpenCL>
{
public:
    typedef BufferPyramidView<T, Levels, TargetDeviceOpenCL> ViewT;
    typedef typename ViewT::ViewType LevelT;
    static const std::size_t LevelCount = Levels;
    
    BufferPyramidManaged() = delete;

    inline BufferPyramidManaged(std::size_t w, std::size_t h, const cl::Context& context, cl_mem_flags flags)
    {        
        // Build power of two structure
        for(std::size_t l = 0; l < LevelCount && (w>>l > 0) && (h>>l > 0); ++l ) 
        {
            const std::size_t new_w = w >> l;
            const std::size_t new_h = h >> l;
            ViewT::imgs[l] = core::Buffer2DView<T,TargetDeviceOpenCL>(new cl::Buffer(context, flags, new_w*new_h*sizeof(T)), new_w, new_h, new_w * sizeof(T));
        }
    }
    
    BufferPyramidManaged(const BufferPyramidManaged<T,LevelCount,TargetDeviceOpenCL>& img) = delete;
    
    inline BufferPyramidManaged(BufferPyramidManaged<T,LevelCount,TargetDeviceOpenCL>&& img) : ViewT(std::move(img))
    {
        
    }
    
    BufferPyramidManaged<T,LevelCount,TargetDeviceOpenCL>& operator=(const BufferPyramidManaged<T,LevelCount,TargetDeviceOpenCL>& img) = delete;
    
    inline BufferPyramidManaged<T,LevelCount,TargetDeviceOpenCL>& operator=(BufferPyramidManaged<T,LevelCount,TargetDeviceOpenCL>&& img)
    {
        ViewT::operator=(std::move(img));
        return *this;
    }
    
    inline ~BufferPyramidManaged()
    {
        for(std::size_t l = 0; l < LevelCount ; ++l)
        {
            if(ViewT::imgs[l].isValid())
            {
                cl::Buffer* clb = static_cast<cl::Buffer*>(ViewT::imgs[l].rawPtr());
                delete clb;
            }
        }
    }
    
    inline const ViewT& view() const { return (const ViewT&)*this; }
    inline ViewT& view() { return (ViewT&)*this; }
};

#endif // CORE_HAVE_OPENCL

}

#endif // CORE_BUFFER_PYRAMID_HPP
