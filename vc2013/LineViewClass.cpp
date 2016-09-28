#include "$safeitemname$.h"

$safeitemname$::$safeitemname$() : LineView() {

}

void $safeitemname$::setup() {

}

$safeitemname$Ref $safeitemname$::create() {
	$safeitemname$Ref ref = $safeitemname$Ref(new $safeitemname$());
	ref->setup();
	return ref;
}