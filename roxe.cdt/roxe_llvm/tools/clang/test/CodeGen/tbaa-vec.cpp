// RUN: %clang_cc1 -triple x86_64-apple-darwin -O1 -disable-llvm-passes %s -emit-llvm -o - | FileCheck %s
// Test TBAA metadata generated by front-end (vector types are always treated as mayalias).

typedef float __m128 __attribute__ ((__vector_size__ (16)));

struct A {
  __m128 a, b;
};

void foo(A *a, __m128 v) {
  // CHECK-LABEL: define void @_Z3fooP1ADv4_f
  a->a = v;
  // CHECK: store <4 x float> %v, <4 x float>* %{{.*}}, align 16, !tbaa [[TAG_char:!.*]]
  // CHECK: store <4 x float> %{{.*}}, <4 x float>* %{{.*}}, align 16, !tbaa [[TAG_char]]
}

// CHECK: [[TYPE_char:!.*]] = !{!"omnipotent char", [[TAG_cxx_tbaa:!.*]],
// CHECK: [[TAG_cxx_tbaa]] = !{!"Simple C++ TBAA"}
// CHECK: [[TAG_char]] = !{[[TYPE_char]], [[TYPE_char]], i64 0}

