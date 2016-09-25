#include<stdio.h>
#include <dlfcn.h>

int main()
{
	int(*func)(char*) = NULL;
	void* handle = NULL;

	handle = dlopen("/home/ravita/workspace/github/0925_code/share_lib_test/utils.so",RTLD_NOW);
	if(!handle)
	{
		printf("Load utils.so fail, err:%s\n", dlerror());
		return -1;
    }

	func = (int(*)(char*)) dlsym(handle, "get_name");
	if(!func)
	{
		printf("Get get_name function fail, err:%s\n", dlerror());
		return -1;
	}

	func("ravita");

	dlclose(handle);
	return 0;
}
