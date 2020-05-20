#include <windows.h>
#include <string>
#include <iostream>

#include "pe_sieve.h"

#define PESIEVE_EXPORTS
#include "pe_sieve_api.h"

#define LIB_NAME "PE-sieve"

pesieve::t_report PESIEVE_API PESieve_scan(pesieve::t_params args)
{
	const pesieve::ReportEx* report = pesieve::scan_and_dump(args);
	if (report == nullptr) {
		pesieve::t_report nullrep = { 0 };
		nullrep.pid = args.pid;
		nullrep.errors = 1;
		return nullrep;
	}
	pesieve::t_report summary = report->scan_report->generateSummary();
	delete report;
	return summary;
}

void PESIEVE_API PESieve_help(void)
{
	std::string my_info = pesieve::info();

	std::cout << my_info;
	MessageBox(NULL, my_info.c_str(), LIB_NAME, MB_ICONINFORMATION);
}

DWORD PESIEVE_API PESieve_version(void)
{
	return pesieve::PESIEVE_VERSION_ID;
}

BOOL WINAPI DllMain (HANDLE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}

