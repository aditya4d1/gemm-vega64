#pragma once

#include"CLHelper.h"

static cl_platform_id platform_id = NULL;
static cl_device_id device_id = NULL;
static cl_context context = NULL;
static cl_command_queue queue = NULL;
static cl_program program = NULL;
static cl_kernel kernel = NULL;
static cl_uint ret_num_platforms, ret_num_devices;
static cl_int error;

std::string LoadKernel(const char* name) {
    std::ifstream in(name);
    std::string result(
            (std::istreambuf_iterator<char>(in)),
            std::istreambuf_iterator<char>());
    return result;
}

void BuildProgram(const std::string& source, cl_context context) {
    size_t lengths[1] = { source.size() };
    const char* sources[1] = { source.data() };
    program = clCreateProgramWithSource(context, 1, sources, lengths, &error);
    CL_CHECK(error);
    error = clBuildProgram(program, 1, &device_id, "", NULL, NULL);
    CL_CHECK(error);
}

cl_program CreateProgram(const std::string& source, cl_context context) {
    size_t lengths[1] = { source.size() };
    const char* sources[1] = { source.data() };

    cl_int error = 0;
    cl_program program = clCreateProgramWithSource(context, 1, sources, lengths, &error);
    return program;
}

void Init() {
    error = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    CL_CHECK(error);
    error = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
    CL_CHECK(error);
    context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &error);
    CL_CHECK(error);
    queue = clCreateCommandQueueWithProperties(context, device_id, NULL, &error);
    CL_CHECK(error);
}

void CreateKernel(std::string Kernel) { 
    kernel = clCreateKernel(program, Kernel.c_str(), &error);
    CL_CHECK(error);
}

namespace stinger {

template<typename T, cl_channel_order Order, cl_channel_type Type, cl_mem_flags Flags>
class Image1D {
public:
    cl_mem img = NULL;
    size_t width, height;
    Tensor<T>& tensor;
    cl_image_format format;
    size_t origin[3];
    size_t region[3];
    Image1D(Tensor<T>& tensor) : 
        width(tensor.width), height(1), tensor(tensor) {
        format.image_channel_order = Order;
        format.image_channel_data_type = Type;
        origin[0] = 0;
        origin[1] = 0;
        origin[2] = 0;
        region[0] = width;
        region[1] = height;
        region[2] = 1;
        cl_image_desc desc ;
        desc.image_type = CL_MEM_OBJECT_IMAGE1D;
        desc.image_width = width;
        desc.image_height = height;
        desc.image_depth = 1;
        desc.image_array_size = 0;
        desc.image_row_pitch = 0;
        desc.image_slice_pitch = 0;
        desc.num_mip_levels = 0;
        desc.num_samples = 0;
        desc.buffer = NULL;

        img = clCreateImage(context, Flags, &format, &desc, NULL, &error);

        CL_CHECK(error);
    }

    void ToGPU() {
        error = clEnqueueWriteImage(queue, img, CL_TRUE,
                    origin, region, 0, 0, tensor.data(), 0, NULL, NULL);
        CL_CHECK(error);
    }

    void FromGPU() {
        error = clEnqueueReadImage(queue, img, CL_TRUE,
                    origin, region, 0, 0, tensor.data(), 0, NULL, NULL);
        CL_CHECK(error);
    }
};


template<typename T, cl_channel_order Order, cl_channel_type Type, cl_mem_flags Flags>
class Image2D {
public:
    cl_mem img = NULL;
    size_t width, height;
    Tensor<T>& tensor;
    cl_image_format format;
    size_t origin[3];
    size_t region[3];
    Image2D(Tensor<T>& tensor) : 
        width(tensor.width), height(tensor.height), tensor(tensor) {
        format.image_channel_order = Order;
        format.image_channel_data_type = Type;
        origin[0] = 0;
        origin[1] = 0;
        origin[2] = 0;
        region[0] = width;
        region[1] = height;
        region[2] = 1;
        cl_image_desc desc ;
        desc.image_type = CL_MEM_OBJECT_IMAGE2D;
        desc.image_width = width;
        desc.image_height = height;
        desc.image_depth = 1;
        desc.image_array_size = 0;
        desc.image_row_pitch = 0;
        desc.image_slice_pitch = 0;
        desc.num_mip_levels = 0;
        desc.num_samples = 0;
        desc.buffer = NULL;

        img = clCreateImage(context, Flags, &format, &desc, NULL, &error);

        CL_CHECK(error);
    }

    void ToGPU() {
        error = clEnqueueWriteImage(queue, img, CL_TRUE,
                    origin, region, 0, 0, tensor.data(), 0, NULL, NULL);
        CL_CHECK(error);
    }

    void FromGPU() {
        error = clEnqueueReadImage(queue, img, CL_TRUE,
                    origin, region, 0, 0, tensor.data(), 0, NULL, NULL);
        CL_CHECK(error);
    }
};

template<typename T, cl_mem_flags flags>
class Buffer1D {
public:
    cl_mem buff = NULL;
    size_t size;
    Tensor<T> &tensor;
    Buffer1D(Tensor<T>& tensor) : tensor(tensor) {
        size = tensor.width * sizeof(T);
        buff = clCreateBuffer(context, flags, size, NULL, &error);
        CL_CHECK(error);
    }

    void ToGPU() {
        error = clEnqueueWriteBuffer(queue, buff, CL_TRUE, 0, size, tensor.ptr, 0, NULL, NULL);
        CL_CHECK(error);
    }

    void FromGPU() {
        error = clEnqueueReadBuffer(queue, buff, CL_TRUE, 0, size, tensor.ptr, 0, NULL, NULL);
        CL_CHECK(error);
    }
};

template<typename T, cl_mem_flags flags>
class Buffer2D {
public:
    cl_mem buff = NULL;
    size_t size;
    Tensor<T> &tensor;
    Buffer2D(Tensor<T>& tensor) : tensor(tensor) {
        size = tensor.width * tensor.height * sizeof(T);
        buff = clCreateBuffer(context, flags, size, NULL, &error);
        CL_CHECK(error);
    }

    void ToGPU() {
        error = clEnqueueWriteBuffer(queue, buff, CL_TRUE, 0, size, tensor.ptr, 0, NULL, NULL);
        CL_CHECK(error);
    }

    void FromGPU() {
        error = clEnqueueReadBuffer(queue, buff, CL_TRUE, 0, size, tensor.ptr, 0, NULL, NULL);
        CL_CHECK(error);
    }
};

}

