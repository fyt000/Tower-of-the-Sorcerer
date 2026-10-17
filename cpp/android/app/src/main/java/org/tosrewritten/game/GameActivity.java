package org.tosrewritten.game;

import android.app.NativeActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;
import java.io.File;
import java.io.ByteArrayOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;

public final class GameActivity extends NativeActivity {
    private void copyAssets(String source, File destination) throws IOException {
        String[] children = getAssets().list(source);
        if (children != null && children.length > 0) {
            if (!destination.isDirectory() && !destination.mkdirs())
                throw new IOException("Cannot create " + destination);
            for (String child : children) copyAssets(source + "/" + child, new File(destination, child));
        } else {
            try (InputStream input = getAssets().open(source);
                 FileOutputStream output = new FileOutputStream(destination)) {
                byte[] buffer = new byte[65536];
                for (int count; (count = input.read(buffer)) != -1;) output.write(buffer, 0, count);
            }
        }
    }

    @Override public void onCreate(Bundle state) {
        // Standard C++ streams need ordinary files. Extract packaged media before raylib starts.
        // Savedat lives alongside game/, so replacing media never replaces user progress.
        try {
            File game = new File(getFilesDir(), "game");
            File assets = new File(game, "assets");
            File marker = new File(game, "asset-version.txt");
            String version;
            try (InputStream input = getAssets().open("assets/asset-version.txt")) {
                ByteArrayOutputStream bytes = new ByteArrayOutputStream();
                byte[] buffer = new byte[256];
                for (int count; (count = input.read(buffer)) != -1;) bytes.write(buffer, 0, count);
                version = new String(bytes.toByteArray(), StandardCharsets.UTF_8);
            }
            if (!marker.isFile() || !new String(Files.readAllBytes(marker.toPath()), StandardCharsets.UTF_8).equals(version)) {
                copyAssets("assets", assets);
                Files.write(marker.toPath(), version.getBytes(StandardCharsets.UTF_8));
            }
        } catch (IOException error) {
            Log.e("TSW", "Unable to prepare game assets", error);
            Toast.makeText(this, "Unable to prepare game assets: " + error.getMessage(), Toast.LENGTH_LONG).show();
            // NativeActivity must not load the game with incomplete assets.
            throw new IllegalStateException("Unable to prepare game assets", error);
        }
        super.onCreate(state);
    }
}
