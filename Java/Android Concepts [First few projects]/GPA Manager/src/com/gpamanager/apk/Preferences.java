package com.gpamanager.apk;

import android.app.Activity;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.os.Bundle;
import android.view.KeyEvent;
import android.widget.LinearLayout;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.Toast;



public class Preferences extends Activity {
	SharedPreferences settings;
	 Editor editor;
	 
	 RadioButton rb0;
		RadioButton rb1;
		RadioButton rb2;
	
		
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_settings);
		
		RadioButton rb0 = (RadioButton)findViewById(R.id.radio0);
		RadioButton rb1 = (RadioButton)findViewById(R.id.radio1);
		RadioButton rb2 = (RadioButton)findViewById(R.id.radio2);
		
		settings = this.getSharedPreferences("data", 0);
		
		setLayout();
		
		String o = settings.getString("Oreintation", "Landscape");
		
		if (o.equals("Portrait")){
			rb0.setChecked(true);
		}else if (o.equals("Landscape")){
			rb1.setChecked(true);
		}else if (o.equals("Both")){
			rb2.setChecked(true);
		}
		
	}
	
	
	public void setLayout(){
		LinearLayout dl = (LinearLayout) findViewById(R.id.set1);
		dl.setBackgroundResource(R.drawable.a_border);
		
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		
	    if (keyCode == KeyEvent.KEYCODE_BACK) {

	    	RadioGroup RG = (RadioGroup)findViewById(R.id.radioGroup1);
			int RD = RG.getCheckedRadioButtonId();
			RadioButton RB = (RadioButton)findViewById(RD);
			
	    	settings = this.getSharedPreferences("data", 0);
			editor = settings.edit();
			
			editor.putString("Oreintation", RB.getText().toString());
			editor.commit();
			
			Toast.makeText(getApplicationContext(), "Saving...", Toast.LENGTH_SHORT).show();
			try {
				Thread.sleep(1000);
			} catch(InterruptedException ex) {
				Thread.currentThread().interrupt();
			}
	        return true;
	    }
	    return super.onKeyDown(keyCode, event);
	
		
	}

	
}
