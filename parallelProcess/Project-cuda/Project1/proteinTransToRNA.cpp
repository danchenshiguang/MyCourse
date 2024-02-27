//If you want to build the file directly at the command prompt then use the following commands. 
//AMD commands
//cl /c saxpy.cpp /I"%AMDAPPSDKROOT%\include"
//link  /OUT:"saxpy.exe" "%AMDAPPSDKROOT%\lib\x86_64\OpenCL.lib" saxpy.obj

//nVIDIA commands
//cl /c saxpy.cpp /I"%NVSDKCOMPUTE_ROOT%\OpenCL\common\inc"
//link  /OUT:"saxpy.exe" "%NVSDKCOMPUTE_ROOT%\OpenCL\common\lib\x64\OpenCL.lib" saxpy.obj

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef __APPLE__
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif
#include <ocl_macros.h>

//Common defines 
#define VENDOR_NAME "AMD"
#define DEVICE_TYPE CL_DEVICE_TYPE_GPU

#define VECTOR_SIZE 1024*1024

//OpenCL kernel which is run for every work item created.
//The below const char string is compiled by the runtime complier
//when a program object is created with clCreateProgramWithSource 
//and built with clBuildProgram.
const char* proteinTransToRNA_kernel =
"void  MyStrcat(char* dstStr, char* srcStr)  \n"
"{                                                   \n"
"   while (*dstStr)                        \n"
"   {                                               \n"
"       dstStr++;                             \n"
"   }                                              \n"
"  while ((*dstStr = *srcStr) != \' \\0 \' )    \n"
 "   {                                                 \n"
 "       dstStr++;                             \n"
 "       srcStr++;                                \n"
"    }                                                \n"
"}                                               \n"
"__kernel void proteinTransToRNA_kernel(       \n"
"                  __global int *repeat,       \n"
"                  __global int *roll,       \n"
"                  __global char **A,       \n"
"                  __global char **R,       \n"
"                  __global char **I,        \n"
"                  __global char **T,        \n"
"                  __global char **P,        \n"
"                  __global char **H,        \n"
"                  __global char **L,        \n"
"                  __global char **Q,        \n"
"                  __global char **result)       \n"
"{                                          \n"
"    //Get the index of the work-item       \n"
"    int index = get_global_id(0);          \n"
"    MyStrcat(result[index],R[(index%roll[0])/repeat[0]]); \n"
"    MyStrcat(result[index],I[(index%roll[1])/repeat[1]]); \n"
"    MyStrcat(result[index],T[(index%roll[2])/repeat[2]]); \n"
"    MyStrcat(result[index],P[(index%roll[3])/repeat[3]]); \n"
"    MyStrcat(result[index],R[(index%roll[4])/repeat[4]]); \n"
"    MyStrcat(result[index],H[(index%roll[5])/repeat[5]]); \n"
"    MyStrcat(result[index],L[(index%roll[6])/repeat[6]]); \n"
"    MyStrcat(result[index],Q[(index%roll[7])/repeat[7]]); \n"
"    MyStrcat(result[index],L[(index%roll[8])/repeat[8]]); \n"
"    MyStrcat(result[index],A[(index%roll[9])/repeat[9]]); \n"
"}                                          \n";
//995328
#define VECTORNUM 6*3*4*4*6*2*6*2*6*4
int main(void) {
    const char* A[4] = { "GCU","GCC","GCA","GCG" };
    const char* R[6] = {"CGU","CGC","CGA","CGG","AGA","AGG"};
    const char* I[3] = { "AUU","AUC","AUA" };
    const char* T[4] = { "ACU","ACC","ACA","ACG" };
    const char* P[4] = { " CCU","CCC","CCA","CCG" };
    const char* H[2] = { " CAU","CAC" };
    const char* L[6] = { "UUA","UUG","CUU","CUC","CUA","CUG" };
    const char* Q[2] = { "CAA","CAG" };
    int num[10] = { 6,3,4,4,6,2,6,2,6,4 };
    char* result[VECTORNUM];//结果向量：维数为995328
    for (int i = 0; i < VECTORNUM; i++)
    {
        result[i] = (char*)malloc(sizeof(char )*30);
        result[i] = (char*)"";
    }
    int repeat[10];
    int roll[10];
    //printf("nn");
    for (int i = 0; i < 10; i++)
    {
        int mul1 = 1;
        int mul2 = 1;
        for (int j = i+1; j < 10; j++)
        {
            mul1 *= num[j];
        }
        for (int j = 0; j <=i; j++)
        {
            mul2 *= num[j];
        }
        repeat[i] = mul1;
        roll[i] = mul2;
    }
    cl_ulong time_start, time_end;
    double total_time;
    cl_int clStatus; //Keeps track of the error values returned. 

    // Get platform and device information
    cl_platform_id* platforms = NULL;

    // Set up the Platform. Take a look at the MACROs used in this file. 
    // These are defined in common/ocl_macros.h
    OCL_CREATE_PLATFORMS(platforms);

    // Get the devices list and choose the type of device you want to run on
    cl_device_id* device_list = NULL;
    OCL_CREATE_DEVICE(platforms[0], DEVICE_TYPE, device_list);

    // Create OpenCL context for devices in device_list
    cl_context context;
    cl_context_properties props[3] =
    {
        CL_CONTEXT_PLATFORM,
        (cl_context_properties)platforms[0],
        0
    };
    // An OpenCL context can be associated to multiple devices, either CPU or GPU
    // based on the value of DEVICE_TYPE defined above.
    context = clCreateContext(NULL, num_devices, device_list, NULL, NULL, &clStatus);
    LOG_OCL_ERROR(clStatus, "clCreateContext Failed...");

    // Create a command queue for the first device in device_list
    cl_command_queue command_queue = clCreateCommandQueue(context, device_list[0], CL_QUEUE_PROFILING_ENABLE, &clStatus);
    LOG_OCL_ERROR(clStatus, "clCreateCommandQueue Failed...");

     //Create memory buffers on the device for each vector
    cl_mem repeat_clmem = clCreateBuffer(context, CL_MEM_READ_ONLY,
        sizeof(int) *10, NULL, &clStatus);
    cl_mem roll_clmem = clCreateBuffer(context, CL_MEM_READ_ONLY,
        sizeof(int) * 10, NULL, &clStatus);
    cl_mem H_clmem = clCreateBuffer(context, CL_MEM_READ_ONLY,
         sizeof(char)*3*2, NULL, &clStatus);
    cl_mem A_clmem = clCreateBuffer(context, CL_MEM_READ_ONLY,
         sizeof(char) * 3*4, NULL, &clStatus);
    cl_mem I_clmem = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
        sizeof(char) * 3*3, NULL, &clStatus);
    cl_mem R_clmem = clCreateBuffer(context, CL_MEM_READ_ONLY,
          sizeof(char) * 3*6, NULL, &clStatus);
    cl_mem L_clmem = clCreateBuffer(context, CL_MEM_READ_ONLY,
          sizeof(char) * 3*6, NULL, &clStatus);
    cl_mem Q_clmem = clCreateBuffer(context, CL_MEM_READ_ONLY,
          sizeof(char) * 3*2, NULL, &clStatus);
    cl_mem P_clmem = clCreateBuffer(context, CL_MEM_READ_ONLY,
          sizeof(char) * 3*4, NULL, &clStatus);
    cl_mem T_clmem = clCreateBuffer(context, CL_MEM_READ_ONLY,
          sizeof(char) * 3*4, NULL, &clStatus);
    cl_mem result_clmem = clCreateBuffer(context, CL_MEM_READ_ONLY,
        VECTORNUM * sizeof(char) * 3*10, NULL, &clStatus);
     

    // Copy the Buffers to the device. We do a blocking write to the device buffer.
    clStatus = clEnqueueWriteBuffer(command_queue, repeat_clmem, CL_TRUE, 0,
        sizeof(int)*10 , repeat, 0, NULL, NULL);
    LOG_OCL_ERROR(clStatus, "clEnqueueWriteBuffer Failed...");

    clStatus = clEnqueueWriteBuffer(command_queue, roll_clmem, CL_TRUE, 0,
        sizeof(int) * 10, roll, 0, NULL, NULL);
    LOG_OCL_ERROR(clStatus, "clEnqueueWriteBuffer Failed...");

    clStatus = clEnqueueWriteBuffer(command_queue, H_clmem, CL_TRUE, 0,
        sizeof(char) * 3 * 2,*H, 0, NULL, NULL);
    LOG_OCL_ERROR(clStatus, "clEnqueueWriteBuffer Failed...");

    clStatus = clEnqueueWriteBuffer(command_queue, I_clmem, CL_TRUE, 0,
        sizeof(char) * 3 * 3, *I, 0, NULL, NULL);
    LOG_OCL_ERROR(clStatus, "clEnqueueWriteBuffer Failed...");

    clStatus = clEnqueueWriteBuffer(command_queue, A_clmem, CL_TRUE, 0,
        sizeof(char) * 3 * 4, *A, 0, NULL, NULL);
    LOG_OCL_ERROR(clStatus, "clEnqueueWriteBuffer Failed...");

    clStatus = clEnqueueWriteBuffer(command_queue, R_clmem, CL_TRUE, 0,
        sizeof(char) * 3 * 6, *R, 0, NULL, NULL);
    LOG_OCL_ERROR(clStatus, "clEnqueueWriteBuffer Failed...");

    clStatus = clEnqueueWriteBuffer(command_queue, P_clmem, CL_TRUE, 0,
        sizeof(char) * 3 * 4, *P, 0, NULL, NULL);
    LOG_OCL_ERROR(clStatus, "clEnqueueWriteBuffer Failed...");

    clStatus = clEnqueueWriteBuffer(command_queue, Q_clmem, CL_TRUE, 0,
        sizeof(char) * 3 * 2, *Q, 0, NULL, NULL);
    LOG_OCL_ERROR(clStatus, "clEnqueueWriteBuffer Failed...");

    clStatus = clEnqueueWriteBuffer(command_queue, L_clmem, CL_TRUE, 0,
        sizeof(char) * 3 * 6, *L, 0, NULL, NULL);
    LOG_OCL_ERROR(clStatus, "clEnqueueWriteBuffer Failed...");

    clStatus = clEnqueueWriteBuffer(command_queue, T_clmem, CL_TRUE, 0,
        sizeof(char) * 3 * 4, *T, 0, NULL, NULL);
    LOG_OCL_ERROR(clStatus, "clEnqueueWriteBuffer Failed...");

    //clStatus = clEnqueueWriteBuffer(command_queue, result_clmem, CL_TRUE, 0,
    //    VECTORNUM * sizeof(char) * 3*10, *result, 0, NULL, NULL);
    //LOG_OCL_ERROR(clStatus, "clEnqueueWriteBuffer Failed...");
 /*    Create a program from the kernel source*/
    cl_program program = clCreateProgramWithSource(context, 1,
        (const char**)&proteinTransToRNA_kernel, NULL, &clStatus);
    LOG_OCL_ERROR(clStatus, "clCreateProgramWithSource Failed...");

    // Build the program
    clStatus = clBuildProgram(program, 1, device_list, NULL, NULL, NULL);
    if (clStatus != CL_SUCCESS)
        LOG_OCL_COMPILER_ERROR(program, device_list[0]);

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "proteinTransToRNA_kernel", &clStatus);

    // Set the arguments of the kernel. Take a look at the kernel definition in saxpy_kernel 
    // variable. First parameter is a constant and the other three are buffers.
    clStatus = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&repeat_clmem);
    clStatus |= clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&roll_clmem);
    //clStatus |= clSetKernelArg(kernel, 2, sizeof(int), (void*)zero);
    clStatus |= clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&A_clmem);
    clStatus |= clSetKernelArg(kernel, 3, sizeof(cl_mem), (void*)&R_clmem);
    clStatus |= clSetKernelArg(kernel, 4, sizeof(cl_mem), (void*)&I_clmem);
    clStatus |= clSetKernelArg(kernel, 5, sizeof(cl_mem), (void*)&T_clmem);
    clStatus |= clSetKernelArg(kernel, 6, sizeof(cl_mem), (void*)&P_clmem);
    clStatus |= clSetKernelArg(kernel, 7, sizeof(cl_mem), (void*)&H_clmem);
    clStatus |= clSetKernelArg(kernel, 8, sizeof(cl_mem), (void*)&L_clmem);
    clStatus |= clSetKernelArg(kernel, 9, sizeof(cl_mem), (void*)&Q_clmem);
    clStatus |= clSetKernelArg(kernel, 10, sizeof(cl_mem), (void*)&result_clmem);

    LOG_OCL_ERROR(clStatus, "clSetKernelArg Failed...");

    // Execute the OpenCL kernel on the list
    size_t global_size = VECTORNUM; // Process one vector element in each work item
    size_t local_size = 144;           // 144
    cl_event proteinTransToRNA_kernel_event;
    clStatus = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,
        &global_size, &local_size, 0, NULL, &proteinTransToRNA_kernel_event);
    LOG_OCL_ERROR(clStatus, "clEnqueueNDRangeKernel Failed...");

    clStatus = clEnqueueReadBuffer(command_queue, result_clmem, CL_TRUE, 0,
        VECTORNUM * 3*10*sizeof(char), result, 1, &proteinTransToRNA_kernel_event, NULL);
    LOG_OCL_ERROR(clStatus, "clEnqueueReadBuffer Failed...");

    // Clean up and wait for all the comands to complete.
    clWaitForEvents(1, &proteinTransToRNA_kernel_event);
    clStatus = clFinish(command_queue);
    clGetEventProfilingInfo(proteinTransToRNA_kernel_event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
    clGetEventProfilingInfo(proteinTransToRNA_kernel_event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);
    total_time = time_end - time_start;
    printf("%s", *result[1]);
    printf("\nExecution time in milliseconds = %0.3f ms\n", (total_time / 1000000.0));

    // Finally release all OpenCL objects and release the host buffers.
    clStatus = clReleaseKernel(kernel);
    clStatus = clReleaseProgram(program);
    clStatus = clReleaseMemObject(repeat_clmem);
    clStatus = clReleaseMemObject(roll_clmem);
    clStatus = clReleaseMemObject(A_clmem);
    clStatus = clReleaseMemObject(H_clmem);
    clStatus = clReleaseMemObject(R_clmem);
    clStatus = clReleaseMemObject(P_clmem);
    clStatus = clReleaseMemObject(T_clmem);
    clStatus = clReleaseMemObject(Q_clmem);
    clStatus = clReleaseMemObject(L_clmem);
    clStatus = clReleaseMemObject(I_clmem);
    clStatus = clReleaseMemObject(result_clmem);
    clStatus = clReleaseCommandQueue(command_queue);
    clStatus = clReleaseContext(context);
    free(*result);
    free(platforms);
    free(device_list);

    return 0;
}