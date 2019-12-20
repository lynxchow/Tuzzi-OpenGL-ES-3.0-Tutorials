/*
* Viry3D
* Copyright 2014-2019 by Stack - stackos@qq.com
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <jni.h>
#include <android/native_window_jni.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>
#include "Tuzzi.h"
#include "string/String.h"
#include "Tutorial_01/DemoApplication.h"
#include "Tutorial_02/ColorApplication.h"
#include "android/TuzziAndroid.h"

using namespace tuzzi;

static JNIEnv* g_env;
static jobject g_jni_obj;

static ANativeWindow *window = nullptr;
static TuzziAndroid *s_tuzzi = nullptr;

static bool g_paused = false;

static int call_activity_method_int(const char* name, const char* sig, ...);
static String call_activity_method_string(const char* name, const char* sig, ...);
static void extract_assets_if_needed(jobject asset_manager, const String& package_path, const String& data_path, bool always_extract);

static void swap_bytes(void* bytes, int size);

extern "C"
{
void
Java_com_tuzzi_lib_Tuzzi_create(JNIEnv *env, jobject obj, jobject surface, jint width, jint height,
                              jobject asset_manager) {
    g_env = env;
    g_jni_obj = obj;


    if (surface != nullptr) {
        window = ANativeWindow_fromSurface(env, surface);
        s_tuzzi = new TuzziAndroid(window);

        SharedPtr<Application> app = MakeShared<ColorApplication>();
        s_tuzzi->loadApplication(app);
    }

    g_paused = false;
}

void Java_com_tuzzi_lib_Tuzzi_onSurfaceDestroy(JNIEnv *env, jobject obj) {
    g_env = env;
    g_jni_obj = obj;
    if (s_tuzzi)
    {
        s_tuzzi->onSurfaceDestory();
    }
    if (window)
    {
        ANativeWindow_release(window);
        window = nullptr;
    }
}

void Java_com_tuzzi_lib_Tuzzi_destroy(JNIEnv *env, jobject obj) {
    g_env = env;
    g_jni_obj = obj;

    if (s_tuzzi)
    {
        s_tuzzi->destroy();
        delete s_tuzzi;
        s_tuzzi = nullptr;
    }
}

void
Java_com_tuzzi_lib_Tuzzi_resize(JNIEnv *env, jobject obj, jobject surface, jint width, jint height) {
    g_env = env;
    g_jni_obj = obj;
}

void Java_com_tuzzi_lib_Tuzzi_pause(JNIEnv *env, jobject obj) {
    g_env = env;
    g_jni_obj = obj;
    s_tuzzi->pause();
}

void Java_com_tuzzi_lib_Tuzzi_resume(JNIEnv *env, jobject obj) {
    g_env = env;
    g_jni_obj = obj;
    s_tuzzi->resume();
}

void Java_com_tuzzi_lib_Tuzzi_draw(JNIEnv *env, jobject obj) {
    g_env = env;
    g_jni_obj = obj;

    if (!g_paused) {
        s_tuzzi->drawFrame();
    }
}

static int call_activity_method_int(const char *name, const char *sig, ...) {
    va_list args;
    va_start(args, sig);

    jclass clazz = g_env->GetObjectClass(g_jni_obj);
    jmethodID methodID = g_env->GetMethodID(clazz, name, sig);
    int result = g_env->CallIntMethodV(g_jni_obj, methodID, args);
    g_env->DeleteLocalRef(clazz);

    va_end(args);

    return result;
}

static String call_activity_method_string(const char *name, const char *sig, ...) {
    va_list args;
    va_start(args, sig);

    jclass clazz = g_env->GetObjectClass(g_jni_obj);
    jmethodID methodID = g_env->GetMethodID(clazz, name, sig);
    jstring str = (jstring) g_env->CallObjectMethodV(g_jni_obj, methodID, args);
    String result = g_env->GetStringUTFChars(str, nullptr);
    g_env->DeleteLocalRef(str);
    g_env->DeleteLocalRef(clazz);

    va_end(args);

    return result;
}

void java_quit_application() {
    call_activity_method_int("quitApplication", "()I");
}
}
