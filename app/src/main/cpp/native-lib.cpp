#include <jni.h>
#include <string>
#include <cinttypes>
#include <android/log.h>
#include <err.h>
#include <inttypes.h>
#include "bzip2/bzlib.h"

#define LOGI(...) \
  ((void)__android_log_print(ANDROID_LOG_INFO, "native-libs::", __VA_ARGS__))
//定义一个宏
#define JAVA_CLASS_PATH "com/keding/nativeutil/NativeRegisterUtil"

extern "C" JNIEXPORT jstring JNICALL
Java_com_keding_nativeutil_BSDiffUtil_getStringFromJni(
        JNIEnv *env,
        jclass clazz) {
    std::string hello = "Hello from C++";
    LOGI("xixixix");
    return env->NewStringUTF(hello.c_str());
}
extern "C" {
extern int main(int argc, char *argv[]);
extern int genpatch(int argc, char *argv[]);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_keding_nativeutil_BSDiffUtil_bsPatch(JNIEnv *env, jclass clazz, jstring old_apk,
                                              jstring patch, jstring output) {
    int argc2 = 4;
    char *argv2[argc2];
    argv2[0] = const_cast<char *>("bspatch");
//    argv2[1] = const_cast<char *>("/storage/emulated/0/oldfile.txt");
//    argv2[2] = const_cast<char *>("/storage/emulated/0/file.patch");
//    argv2[3] = const_cast<char *>("/storage/emulated/0/newfile.txt");
//    argv2[1] = (char *) *env->GetStringUTFChars(old_apk, 0);
//    argv2[2] = (char *) *env->GetStringUTFChars(output, 0);
//    argv2[3] = (char *) *env->GetStringUTFChars(patch, 0);
//    LOGI("calculation time: %" PRIu64,"sds");
    //输出debug级别的日志信息
    char **argv;
    argv = (char **) malloc(4 * sizeof(char *));
    argv[0] = "bspatch";
    argv[1] = (char *) env->GetStringUTFChars(old_apk, 0);
    argv[2] = (char *) env->GetStringUTFChars(output, 0);
    argv[3] = (char *) env->GetStringUTFChars(patch, 0);
    main(4, argv);
}extern "C"
JNIEXPORT jint JNICALL
Java_com_keding_nativeutil_BSDiffUtil_genDiff(JNIEnv *env, jclass clazz, jstring old_apk_path,
                                              jstring new_apk_path, jstring patch_path) {

    int argc = 4;
    char *argv[argc];
    argv[0] = "bsdiff";

    argv[1] = (char *) env->GetStringUTFChars(old_apk_path, 0);
    argv[2] = (char *) env->GetStringUTFChars(new_apk_path, 0);
    argv[3] = (char *) env->GetStringUTFChars(patch_path, 0);

    printf("old apk = %s \n", argv[1]);
    printf("new apk = %s \n", argv[2]);
    printf("patch = %s \n", argv[3]);

    int ret = genpatch(argc, argv);

    printf("genDiff result = %d ", ret);

    env->ReleaseStringUTFChars(old_apk_path, argv[1]);
    env->ReleaseStringUTFChars(new_apk_path, argv[2]);
    env->ReleaseStringUTFChars(patch_path, argv[3]);
}



// 注册的方式,推荐

extern "C"
JNIEXPORT jstring JNICALL
get_string_register(JNIEnv *env, jclass clazz) {

    return env->NewStringUTF("我是来自C++的通过注册的方式调用的方法");
}

extern "C"
JNIEXPORT jstring JNICALL
get_string_register2(JNIEnv *env, jclass clazz) {

    return env->NewStringUTF("我是来自C++的通过注册的方式调用的方法22222222");
}

// 后续添加新方法
static JNINativeMethod g_methods[] = {
        {"getStringFromNative", "()Ljava/lang/String;", (void *) get_string_register},
        {"getStringFromNative2", "()Ljava/lang/String;", (void *) get_string_register2}

};

// 库被加载到虚拟机的时候自动触发该函数
jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    LOGI("jclazz1");
    vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6);
    jclass jclazz = env->FindClass(JAVA_CLASS_PATH);
    LOGI("jclazz");
    // 方法映射表和方法数
    env->RegisterNatives(jclazz, g_methods, sizeof(g_methods) / sizeof(g_methods[0]));
    return JNI_VERSION_1_6;
}


