#include "TestTextViewHeader.h"

TestTextViewHeader::TestTextViewHeader() : TextView() {

}

void TestTextViewHeader::setup() {

}

TestTextViewHeaderRef TestTextViewHeader::create() {
	TestTextViewHeaderRef ref = TestTextViewHeaderRef(new TestTextViewHeader());
	ref->setup();
	return ref;
}