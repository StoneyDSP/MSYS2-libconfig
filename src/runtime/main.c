#include "runtime/main.h"

#if defined(ID_VOID_MAIN)
void main() {}
#else
#	if defined(__CLASSIC_C__)
int main(argc, argv) int argc; char *argv[];
#	else
int main(int argc, char* argv[])
#	endif /** __CLASSIC_C__ */
{
	int require = 0;

	require += path_seperator[argc];
	require += string_seperator[argc];
	require += homedrive[argc];
	require += rootdir[argc];

	require += prefix[argc];

	require += bindir[argc];
	require += datadir[argc];
	require += includedir[argc];
	require += infodir[argc];
	require += libdir[argc];
	require += licensedir[argc];
	require += libexecdir[argc];
	require += localedir[argc];
	require += localstatedir[argc];
	require += mandir[argc];
	require += sbindir[argc];
	require += sharedstatedir[argc];
	require += sysconfdir[argc];

// #if defined(HAVE_LIBCURL)
// 	require += have_libcurl[argc];
// #endif

// #if defined(HAVE_LIBGPGME)
// 	require += have_libgpgme[argc];
// #endif

#if defined(HAVE_LIBSSL)
	require += have_libssl[argc];
#endif

#if defined(HAVE_LIBNETTLE)
	require += have_libnettle[argc];
#endif

	(void)argv;
	return require;
}
#endif /** ID_VOID_MAIN */
