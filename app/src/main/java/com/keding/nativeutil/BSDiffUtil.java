package com.keding.nativeutil;

/**
 * @author: skd
 * @date 2019-11-04
 * @Desc BSDiffUtil
 */
public class BSDiffUtil {
    static {
        System.loadLibrary("bsdiff");
    }

    public static native  void bsPatch(String oldApk, String patch, String output);

    public static native String getStringFromJni();

    /**
     * native方法 比较路径为oldPath的apk与newPath的apk之间差异，并生成patch包，存储于patchPath
     *
     * 返回：0，说明操作成功
     *
     * @param oldApkPath 示例:/sdcard/old.apk
     * @param newApkPath 示例:/sdcard/new.apk
     * @param patchPath  示例:/sdcard/xx.patch
     * @return
     */
    public static native int genDiff(String oldApkPath, String newApkPath, String patchPath);
}
