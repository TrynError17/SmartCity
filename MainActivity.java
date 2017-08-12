package com.example.user.tne;


import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.webkit.WebView;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {


    Button reset;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        String url = "https://thingspeak.com/channels/316033/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=1000&sum=15&title=Car+&type=spline&xaxis=Time&yaxis=Car";
        WebView view = (WebView) findViewById(R.id.webview1);

        view.getSettings().setJavaScriptEnabled(true);
        view.loadUrl(url);

        String url2 = "https://thingspeak.com/channels/316033/charts/2?bgcolor=%23ffffff&color=%23d62020&dynamic=true&results=100&type=column&average=60";
        WebView view2 = (WebView) findViewById(R.id.webview2);

        view2.getSettings().setJavaScriptEnabled(true);
        view2.loadUrl(url2);
        

    }
}
