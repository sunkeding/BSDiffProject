package com.keding.cdemo2;

import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import com.keding.nativeutil.BSDiffUtil;
import com.keding.nativeutil.NativeRegisterUtil;

import java.io.File;

/**
 * @author: skd
 * @date 2019-11-01
 * @Desc MainActivity
 */
public class MainActivity extends AppCompatActivity {
    String oldApk = new File(Environment.getExternalStorageDirectory(), "oldfile.txt").getAbsolutePath();
    String patch = new File(Environment.getExternalStorageDirectory(), "file.patch").getAbsolutePath();
    String output = new File(Environment.getExternalStorageDirectory(), "newfile.txt").getAbsolutePath();


    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        dealPatch();
        Log.d("MainActivity", BSDiffUtil.getStringFromJni());
        Log.d("MainActivity", NativeRegisterUtil.getStringFromNative());
        Log.d("MainActivity", NativeRegisterUtil.getStringFromNative2());
    }

    private void dealPatch() {
        if (ContextCompat.checkSelfPermission(MainActivity.this, android.Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(MainActivity.this, new String[]{android.Manifest.permission.WRITE_EXTERNAL_STORAGE}, 2);
        } else {
            BSDiffUtil.bsPatch(oldApk, patch, output);

        }
    }

//    public native void bsPatch(String oldApk, String patch, String output);
//    public native String getStringFromJni();

//    /**
//     * native方法 比较路径为oldPath的apk与newPath的apk之间差异，并生成patch包，存储于patchPath
//     *
//     * 返回：0，说明操作成功
//     *
//     * @param oldApkPath 示例:/sdcard/old.apk
//     * @param newApkPath 示例:/sdcard/new.apk
//     * @param patchPath  示例:/sdcard/xx.patch
//     * @return
//     */
//    public static native int genDiff(String oldApkPath, String newApkPath, String patchPath);

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        if (requestCode == 2) {
            if (grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                BSDiffUtil.bsPatch(oldApk, patch, output);

            }
        }
    }
}
