
__kernel void Main(__global float4 *A) {
    int lid = get_local_id(0);
    float4 a;

    __asm(
    "global_load_dwordx4 %0, %1, off \n"
    :"=v"(a)
    :"v"(A + lid));

    a = a + a;

    __asm(
    "global_store_dwordx4 %0, %1, off"
    :
    :"v"(A + lid), "v"(a));

}
