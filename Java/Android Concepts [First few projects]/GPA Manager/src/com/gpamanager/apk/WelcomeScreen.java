package com.gpamanager.apk;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.Toast;

public class WelcomeScreen extends Activity {

	
	Editor editor;
	SharedPreferences settings;
	SharedPreferences pro;
	String Ac;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		
		setContentView(R.layout.activity_welcome_screen);
		Intent i = this.getIntent();
		Ac = i.getStringExtra("Action");
		settings = this.getSharedPreferences("data", 0);
		
		
	}

	
	
	public void HideKeyBoard(View v){
		 InputMethodManager inputManager = (InputMethodManager)            
				  this.getSystemService(Context.INPUT_METHOD_SERVICE); 
				    inputManager.hideSoftInputFromWindow(this.getCurrentFocus().getWindowToken(),      
				    InputMethodManager.HIDE_NOT_ALWAYS);
	}

	@SuppressLint("NewApi")
	public void NewProfileWelcome(View v){
		
	EditText f = (EditText) findViewById(R.id.welcome_first);
	EditText l = (EditText) findViewById(R.id.welcome_last);
	TextView lbl = (TextView) findViewById(R.id.welcome_label);
			RadioGroup RG = (RadioGroup)findViewById(R.id.radioGroupqors);
		int RD = RG.getCheckedRadioButtonId();
		RadioButton RB = (RadioButton)findViewById(RD);
		String profile_name;
		
		if (new String(f.getText().toString()).equals("") || new String(l.getText().toString()).equals("") ){ //If Empty
		lbl.setText("Enter your name");
		}else if(new String(f.getText().toString()).contains(" ") || new String(l.getText().toString()).contains(" ")){ //If It has a space
			lbl.setText("Make sure there are no spaces.");
		}else{
			 if (new String(f.getText().toString()).matches("[A-Za-z]+") != true || new String(l.getText().toString()).matches("[A-Za-z]+") != true){
				 lbl.setText("Special characters or numbers are not permitted.");
			 }else{
				 profile_name = f.getText().toString() + "_" + l.getText().toString();
				File Profiles = new File(getApplicationInfo().dataDir + "/Profiles/" + profile_name);
				Profiles.setExecutable(true, false);
				Profiles.setReadable(true, false);
				Profiles.setWritable(true, false);
				if (Profiles.exists()){
					Toast.makeText(getApplicationContext(), "A profile with this name exists.", Toast.LENGTH_SHORT).show();
				}else{
					Profiles.mkdirs();
					File o;
					new File(getApplicationInfo().dataDir + "/Profiles/" + profile_name + "/Fall").mkdirs();
					new File(getApplicationInfo().dataDir + "/Profiles/" + profile_name + "/Spring").mkdirs();
					try {
						o = new File(getApplicationInfo().dataDir + "/Profiles/" + profile_name + "/Fall/Classes");
						o.setExecutable(true, false);
						o.setReadable(true, false);
						o.setWritable(true, false);
						o.createNewFile();
						o = new File(getApplicationInfo().dataDir + "/Profiles/" + profile_name + "/Fall/CreditHours");
						o.setExecutable(true, false);
						o.setReadable(true, false);
						o.setWritable(true, false);
						o.createNewFile();
						o = new File(getApplicationInfo().dataDir + "/Profiles/" + profile_name + "/Fall/Grades");
						o.setExecutable(true, false);
						o.setReadable(true, false);
						o.setWritable(true, false);
						o.createNewFile();
						
						o = new File(getApplicationInfo().dataDir + "/Profiles/" + profile_name + "/Spring/Classes");
						o.setExecutable(true, false);
						o.setReadable(true, false);
						o.setWritable(true, false);
						o.createNewFile();
						o = new File(getApplicationInfo().dataDir + "/Profiles/" + profile_name + "/Spring/CreditHours");
						o.setExecutable(true, false);
						o.setReadable(true, false);
						o.setWritable(true, false);
						o.createNewFile();
						o = new File(getApplicationInfo().dataDir + "/Profiles/" + profile_name + "/Spring/Grades");
						o.setExecutable(true, false);
						o.setReadable(true, false);
						o.setWritable(true, false);
						o.createNewFile();
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					
					if(RB.getText().toString().equalsIgnoreCase("Quarter")){
						new File(getApplicationInfo().dataDir + "/Profiles/" + profile_name + "/Winter").mkdirs();	
						
						try {
							o = new File(getApplicationInfo().dataDir + "/Profiles/" + profile_name + "/Winter/Classes");
							o.setExecutable(true, false);
							o.setReadable(true, false);
							o.setWritable(true, false);
							o.createNewFile();
							o = new File(getApplicationInfo().dataDir + "/Profiles/" + profile_name + "/Winter/CreditHours");
							o.setExecutable(true, false);
							o.setReadable(true, false);
							o.setWritable(true, false);
							o.createNewFile();
							o = new File(getApplicationInfo().dataDir + "/Profiles/" + profile_name + "/Winter/Grades");
							o.setExecutable(true, false);
							o.setReadable(true, false);
							o.setWritable(true, false);
							o.createNewFile();
							
						} catch (IOException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
					}
					
					
					
					
					if (Ac.equals("Welcome")){
										 pro = this.getSharedPreferences("profile_0", 0);
								 editor = pro.edit();
							editor.putString("Profile_Name", profile_name);
							editor.putString("First_Name", f.getText().toString());
							editor.putString("Last_Name", l.getText().toString());	
							editor.putString("Mester", RB.getText().toString());
							editor.commit();
			
						this.finish();
						Intent openMainActivity= new Intent(this, MainActivity.class);
						openMainActivity.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
						startActivity(openMainActivity);
						
						editor = settings.edit();
						editor.putInt("LastLoaded", 0);
						editor.commit();
						
						Toast.makeText(getApplicationContext(), "Welcome, Thanks for downloading.", Toast.LENGTH_SHORT).show();
						try {
							Thread.sleep(1000);
						} catch(InterruptedException ex) {
							Thread.currentThread().interrupt();
						}
			
					}else if(Ac.equals("New Profile")){
						File[] file = new File(getApplicationInfo().dataDir + "/shared_prefs").listFiles();
						List<String> pl = new ArrayList<String>();
						for (File fl: file){
							if (!fl.getName().substring(0, fl.getName().lastIndexOf(".")).equals("data")){
						pl.add(fl.getName().substring(0, fl.getName().lastIndexOf(".")));
						}
						}
						int i = pl.size() - 1;
						
						 pro = this.getSharedPreferences("profile_" + String.valueOf(i) , 0);
						 editor = pro.edit();
					editor.putString("Profile_Name", profile_name);
					editor.putString("First_Name", f.getText().toString());
					editor.putString("Last_Name", l.getText().toString());	
					editor.putString("Mester", RB.getText().toString());
					editor.commit();
					
					this.finish();
					Intent openMainActivity= new Intent(this, MainActivity.class);
					openMainActivity.setFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
					startActivity(openMainActivity);
					
					editor = settings.edit();
					editor.putInt("LastLoaded", i);
					editor.commit();
					
					Toast.makeText(getApplicationContext(), "Creating...", Toast.LENGTH_SHORT).show();
					try {
						Thread.sleep(1000);
					} catch(InterruptedException ex) {
						Thread.currentThread().interrupt();
					}
					this.finish();
					
					}
	
			
}

			
		}
			 }
	
	
	}
}
