package com.gpamanager.apk;

import android.app.Activity;
import android.content.pm.PackageManager.NameNotFoundException;
import android.os.Bundle;
import android.widget.TextView;

public class About extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_about);
		TextView tv = (TextView) findViewById(R.id.textView1);
		try {
			tv.setText("Version " + getApplicationContext().getPackageManager().getPackageInfo(this.getPackageName(), 0).versionName + 
					" © 2014 Tolu Salako.");
		} catch (NameNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}



}
