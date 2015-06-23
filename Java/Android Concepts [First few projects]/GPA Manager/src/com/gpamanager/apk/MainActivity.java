/*Made by
 * Toluwanimi Salako
 * Dec 25, 2013
 */
package com.gpamanager.apk;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.ClipData;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.content.res.Configuration;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.ContextMenu;
import android.view.ContextMenu.ContextMenuInfo;
import android.view.Gravity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.DragShadowBuilder;
import android.view.View.OnLongClickListener;
import android.view.View.OnTouchListener;
import android.view.ViewGroup.LayoutParams;
import android.view.inputmethod.InputMethodManager;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.ViewFlipper;
import android.widget.RelativeLayout;
import android.widget.ScrollView;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {

	public File defpath(){
	PackageManager m = getPackageManager();
	String s = getPackageName();
	try {
	    PackageInfo p = m.getPackageInfo(s, 0);
	    s = p.applicationInfo.dataDir;
	} catch (NameNotFoundException e) {
	    Log.w("yourtag", "Error Package name not found ", e);
	}
	return new File(s);
}
    private ViewFlipper vf;
    private float lastX;
	String Cu_User;
	List <String> profilelist = new ArrayList<String>();
	 SharedPreferences settings; 
	 SharedPreferences Cu_profile;
	 SharedPreferences Cu_gradescale;
	 SharedPreferences.Editor editor;
	 LinearLayout Fall, Winter, Spring;
	 List<LinearLayout> FallClasses = new ArrayList<LinearLayout>(),
			 WinterClasses =new ArrayList<LinearLayout>(), SpringClasses = new ArrayList<LinearLayout>();
	 GPA gpaFall = new GPA(), gpaWinter = new GPA(), gpaSpring = new GPA();
	 
		@Override
		protected void onCreate(Bundle savedInstanceState) {
			super.onCreate(savedInstanceState);
			//requestWindowFeature(Window.FEATURE_CUSTOM_TITLE);
			//requestWindowFeature(Window.FEATURE_NO_TITLE);
	
			setContentView(R.layout.activity_main);

            vf = (ViewFlipper) findViewById(R.id.view_flipper);
		    vf.setOnTouchListener(new MyTouchListener2());

			settings = this.getSharedPreferences("data", 0);
			
			Cu_profile = this.getSharedPreferences("profile_0", 0);  //Load Default profile. 
			
			Cu_gradescale = this.getSharedPreferences("scale_default", 0); //Load default scale. TODO: Create this first
			
			if (new File(defpath().getPath() + "/shared_prefs/profile_0.xml").exists()){
				int i = settings.getInt("LastLoaded", 0);
			Cu_profile = this.getSharedPreferences("profile_" + String.valueOf(i), 0); // OR Load Last used
			try {
				StartUpLoad();
				LoadProfile(i);
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			}else{
			StartUpChecks();
			}

		}
			
		@Override
	    public void onConfigurationChanged(Configuration newConfig) {
	        super.onConfigurationChanged(newConfig);
	        FrameLayout rl2 = (FrameLayout) findViewById(R.id.rd2);
	        RelativeLayout rl =(RelativeLayout) findViewById(R.id.rd);
	        
	        LinearLayout fl = (LinearLayout) findViewById(R.id.fl);
	       // LinearLayout r3 = (LinearLayout) findViewById(R.id.fl);
	         if (newConfig.orientation == Configuration.ORIENTATION_LANDSCAPE) {
	        	 
	        	 rl.setVisibility(View.GONE);
	        	 
	        	 rl2.setVisibility(View.GONE);
	        	 
	        	 if(settings.getBoolean("Landscape", true) || settings.getBoolean("Both", true)){
	        		 fl.setVisibility(View.VISIBLE);
	        		 
	        	 }
	        	 
	        	 
	            } else if (newConfig.orientation == Configuration.ORIENTATION_PORTRAIT){
	            
		        	 rl.setVisibility(View.VISIBLE);
		        	 
		        	 rl2.setVisibility(View.VISIBLE); 
		        	 
		        	 if(settings.getBoolean("Portrait", false) || settings.getBoolean("Both", true)){
		        		 fl.setVisibility(View.VISIBLE);
		        		 
		        	 }
	            }
	    }

    private final class MyTouchListener2 implements OnTouchListener {
        public boolean onTouch(View view, MotionEvent touchevent) {
            switch (touchevent.getAction())
            {
                case MotionEvent.ACTION_DOWN:
                {
                    lastX = touchevent.getX();
                    break;
                }
                case MotionEvent.ACTION_UP:
                {
                    float currentX = touchevent.getX();
                    if (lastX < currentX)
                    {
                        if (vf.getDisplayedChild()==0) break;
                        vf.setInAnimation(getApplicationContext(), R.anim.in_from_left);
                        vf.setOutAnimation(getApplicationContext(), R.anim.out_to_right);
                        vf.showNext();
                    }
                    if (lastX > currentX)
                    {
                        if (vf.getDisplayedChild()==1) break;
                        vf.setInAnimation(getApplicationContext(), R.anim.in_from_right);
                        vf.setOutAnimation(getApplicationContext(), R.anim.out_to_left);
                        vf.showPrevious();
                    }
                    break;
                }
            }
            return false;
        }
    }
	
		
		@Override
		public boolean onCreateOptionsMenu(Menu menu) {
			// Inflate the menu; this adds items to the action bar if it is present.
			getMenuInflater().inflate(R.menu.main, menu);
			return true;
		}
		
		@Override
		public void onCreateContextMenu(ContextMenu menu, View v, ContextMenuInfo menuInfo){
			
			super.onCreateContextMenu(menu, v, menuInfo); 
			menu.clear();
	        int i =0;
		    menu.setHeaderTitle("Profile Menu"); 
		    for (String s: profilelist){
		    	
		    	Cu_profile = this.getSharedPreferences(s, 0);
		    menu.add(0, v.getId(), i, Cu_profile.getString("First_Name", ""));
		    	
		    i++;
		    //TODO Fix this
		    }
		}
		
	       @Override  
	       public boolean onContextItemSelected(MenuItem item) {  
	    	   int i = item.getOrder();
	        try {
				LoadProfile(i);
				editor = settings.edit();
				editor.putInt("LastLoaded", i);
				editor.commit();
				Toast.makeText(getApplicationContext(), "Load Successful", Toast.LENGTH_SHORT).show();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				Toast.makeText(getApplicationContext(), "Load Unsuccessful", Toast.LENGTH_SHORT).show();
			}
	        
	       return true;  
	       }  
	
		
@Override
protected void onSaveInstanceState(Bundle savedInstanceState){}
		
	 public class GPA{
	
		double[][] gparray = new double[2][10];
		String[] classes = new String[10];
		
		double totalgp = 0, totalch = 0;
		 public GPA(){
			//////////
		 }
	
	 private double Grade (String grade){
		//TODO: FIx grades
		 if (grade.equals("A")){
			 return 4;
		 }else if(grade.equals("A-")){
			 return 3.7;
		 } else if(grade.equals("B+")){
			 return 3.33;
		 }else if(grade.equals("B")){
			 return 3;
		 }else if(grade.equals("B-")){
			 return 2.7;
		 }else if(grade.equals("C+")){
			 return 2.30;
		 }else if(grade.equals("C")){
			 return 2;
		 }else if(grade.equals("C-")){
			 return 1.7;
		 }else if(grade.equals("D+")){
			 return 1.3;
		 }else if(grade.equals("D")){
			 return 1;
		 }else if(grade.equals("D-")){
			 return .7;
		 }else {
			 return 0;
		 }
		 
	 }
	 
	 public void addGrade(double credithours, String grade, String subject){
		 
		for (int j = 0; j < 10; j++){
			
		if (gparray[0][j] == 0){
		classes[j] = subject;
		 gparray[0][j] = Grade(grade);
		 gparray[1][j] = credithours;
		 break;
		}else{
			
		}
		}
	 }
	 
	 public double getGPA(){
		 totalgp = 0; totalch = 0;
		 
		for (int i = 0; i < 10; i++){
		 totalgp += gparray[0][i] * gparray[1][i];
		totalch += gparray[1][i];
		 }
		 
		 return totalgp/totalch;
	 }
	 }
	 
	 public void updateGPA(){
		 TextView tv = (TextView) findViewById(R.id.gpa_name);
		 tv.setText(Cu_User + ", your GPA(s):");
		 tv = (TextView) findViewById(R.id.gpa_gpa);
		 
		 if (new String(Cu_profile.getString("Mester", "")).toString().equalsIgnoreCase("Semester")){
		 tv.setText("Fall: " + String.valueOf((double) Math.round(gpaFall.getGPA()* 100)/100) + "\n"+
				 	"Spring: " + String.valueOf((double) Math.round(gpaSpring.getGPA()* 100)/100)
				 	+ "\n"+
				 	"Cumulative: " + String.valueOf((double) Math.round(getCumulative(gpaFall, null, gpaSpring)* 100)/100));
		 }else{
			 tv.setText("Fall: " + String.valueOf((double) Math.round(gpaFall.getGPA()* 100)/100) + "\n"+
					 "Winter: " + String.valueOf((double) Math.round(gpaWinter.getGPA()* 100)/100) + "\n"+
					 	"Spring: " + String.valueOf((double) Math.round(gpaSpring.getGPA()* 100)/100)+
					 	"\n" +
			 "Cumulative: " + String.valueOf((double) Math.round(getCumulative(gpaFall, gpaWinter, gpaSpring)* 100)/100));
		 }
		 
		 
		 
	 }
	 
	 public void HideKeyBoard(View v){
		 InputMethodManager inputManager = (InputMethodManager)            
				  this.getSystemService(Context.INPUT_METHOD_SERVICE); 
				    inputManager.hideSoftInputFromWindow(this.getCurrentFocus().getWindowToken(),      
				    InputMethodManager.HIDE_NOT_ALWAYS);
	}
	 
	 public double getCumulative(GPA fall, GPA winter, GPA spring){
		double tgp, tch;
		tgp = fall.totalgp + spring.totalgp;
		tch = fall.totalch + spring.totalch;
		 if (!(winter == null)){
			 tgp += winter.totalgp;
			 tch += winter.totalch;
		 }
		 
			return tgp/tch;
	 }
	 public void StartUpLoad(){
		 Cu_User = Cu_profile.getString("First_Name", "").toString();
		 
			//Populate Grades and Hours///////////////////////////////////////////////////////////////////////
			ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(
					  this, R.array.grades, android.R.layout.simple_spinner_item );
					adapter.setDropDownViewResource( android.R.layout.simple_spinner_dropdown_item );
					Spinner s = (Spinner) findViewById( R.id.grade);
					s.setAdapter( adapter );
					
					adapter = ArrayAdapter.createFromResource(
							  this, R.array.credits, android.R.layout.simple_spinner_item );
							adapter.setDropDownViewResource( android.R.layout.simple_spinner_dropdown_item );
							s = (Spinner) findViewById( R.id.credit );
							s.setAdapter( adapter );
			/////////////////////////////////////////////////////////////////////////////////////////////////////
		  
		
		 
	 }
	 
	 public void LoadProfile(int i) throws IOException{
		 Cu_profile = this.getSharedPreferences("profile_" + String.valueOf(i), 0);
		 Cu_User = Cu_profile.getString("First_Name", "");
		 LoadProfiletolist();
		 Clear();
		 SetupLayout();
		 Load();
		 updateGPA();
	 }
	 public void LoadProfiletolist(){
			/////GET PROFILE LIST///////////////////
		 profilelist.clear();
			File[] file = new File(getApplicationInfo().dataDir + "/shared_prefs").listFiles();
			
			for (File f: file){
				if (!f.getName().substring(0, f.getName().lastIndexOf(".")).equals("data")){
			profilelist.add(f.getName().substring(0, f.getName().lastIndexOf(".")));
				}
				
			}

		 
	 }

	
	public void StartUpChecks(){ //To create Settings Files
	
			Intent showwelcome = new Intent(this, WelcomeScreen.class);
			showwelcome.putExtra("Action", "Welcome");
			if (showwelcome.resolveActivity(getPackageManager()) != null) {
			    startActivity(showwelcome);
			}
			editor = settings.edit();
			editor.putBoolean("Portrait", false);
			editor.putBoolean("Landscape", true);
			editor.putBoolean("Both", false);
			editor.commit();
		    this.finish();
	}
	
	
	public void SetupLayout(){ //Based on mester type
		 
			//Loads newly created profile
		String h = "Hello " + Cu_User + ",";
		
		String z = "Add your classes for this " + new String(Cu_profile.getString("Mester", ""));

		TextView textv = (TextView) findViewById(R.id.main_lbl);
		textv.setText(h);
		((TextView) findViewById(R.id.main_lbl2)).setText(z);
		registerForContextMenu(textv);
		
		ToluLayout NW = new ToluLayout();
        ViewFlipper mainbase = (ViewFlipper) findViewById(R.id.view_flipper);

        LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT));
        LinearLayout.LayoutParams paramf = new LinearLayout.LayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT));

        LinearLayout ff = new LinearLayout(this);
        LinearLayout ww = new LinearLayout(this);
        LinearLayout ss = new LinearLayout(this);
		/////////////////////////////////////
		ScrollView f_cur = new ScrollView(this);
		f_cur.setLayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT,LayoutParams.WRAP_CONTENT));
		LinearLayout f_baby = new LinearLayout(this);
		f_baby.setOrientation(LinearLayout.VERTICAL);
		f_baby.setLayoutParams(new LinearLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT));
		/////////////////////////////////////
		ScrollView s_cur = new ScrollView(this);
		s_cur.setLayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT,LayoutParams.WRAP_CONTENT));
		LinearLayout s_baby = new LinearLayout(this);
		s_baby.setOrientation(LinearLayout.VERTICAL);
		s_baby.setLayoutParams(new LinearLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT));
		///
		RadioButton tv = (RadioButton) findViewById(R.id.rb1);
		tv.setText("FALL");
		tv = (RadioButton) findViewById(R.id.rb2);
		tv.setText("WINTER");
		tv = (RadioButton) findViewById(R.id.rb3);
		tv.setText("SPRING");
		
		//Fall = (LinearLayout) findViewById(R.id.fallout);
		Fall = NW.NewQuarter("Fall");
		//Fall.setBackgroundColor(Color.parseColor("#FFFFFF"));
		Fall.setBackgroundResource(R.drawable.b_border);
		f_baby.addView(Fall);
		f_cur.addView(f_baby);
		ff.addView(f_cur);
        mainbase.addView(ff, paramf);

	if (new String(Cu_profile.getString("Mester", "")).toString().equalsIgnoreCase("Semester")){
		
			tv = (RadioButton) findViewById(R.id.rb2);
			tv.setVisibility(View.INVISIBLE);
			Spring = NW.NewQuarter("SPRING");
			//Spring.setBackgroundColor(Color.parseColor("#FFFFFF"));
			Spring.setBackgroundResource(R.drawable.b_border);
			s_baby.addView(Spring, params);
			s_cur.addView(s_baby);
			ss.addView(s_cur);

        mainbase.addView(ss, paramf);

		}else{
			ScrollView w_cur = new ScrollView(this);
			LinearLayout w_baby = new LinearLayout(this);
			w_baby.setOrientation(LinearLayout.VERTICAL);
			w_baby.setLayoutParams(new LinearLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT));
			Winter = NW.NewQuarter("WINTER");
			w_cur.setLayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT,LayoutParams.WRAP_CONTENT));
			w_baby.addView(Winter, params);
			//Winter.setBackgroundColor(Color.parseColor("#FFFFFF"));
			Winter.setBackgroundResource(R.drawable.b_border);
			w_cur.addView(w_baby);
			ww.addView(w_cur);
			////////
			tv = (RadioButton) findViewById(R.id.rb2);
			tv.setVisibility(View.VISIBLE);
			Spring = NW.NewQuarter("SPRING");
			//Spring.setBackgroundColor(Color.parseColor("#FFFFFF"));
			Spring.setBackgroundResource(R.drawable.b_border);
			s_baby.addView(Spring);
			s_cur.addView(s_baby);
			ss.addView(s_cur);

        mainbase.addView(ww, paramf);
        mainbase.addView(ss, paramf);
		}
	
	
	}
	
	
	 @Override
	    public boolean onOptionsItemSelected(MenuItem item)
	    {
	        
	
	        if (item.getItemId() == R.id.action_save) {
	        	try {
					Save();
					Toast.makeText(getApplicationContext(), "Successfully Saved", Toast.LENGTH_SHORT).show();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
					Toast.makeText(getApplicationContext(), "Save Unsuccessful", Toast.LENGTH_SHORT).show();
				}
	            
	            return true;
	        }else if (item.getItemId() ==   R.id.action_clear) {
	        	Clear();
	        	SetupLayout();
	        	updateGPA();
	            Toast.makeText(getApplicationContext(), "Cleared", Toast.LENGTH_SHORT).show();
	            return true;
	 
	        }else if (item.getItemId() ==  R.id.action_preferences){
	        	Intent i = new Intent(getApplicationContext(), Preferences.class);
				if (i.resolveActivity(getPackageManager()) != null) {
					
				    startActivity(i);
				}
	            return true;
	           
	        }else if (item.getItemId() == R.id.action_about){
	        
	        	Intent i = new Intent(getApplicationContext(), About.class);
				if (i.resolveActivity(getPackageManager()) != null) {
				    startActivity(i);
				}
	        	return true;
	        }else if (item.getItemId() == R.id.action_new){
	        	if (!FallClasses.isEmpty()){
	        	AlertDialog.Builder builder = new AlertDialog.Builder(this);
	        	builder.setMessage("Do you want to save first?").setPositiveButton("Yes", dialogClickListener)
	        	    .setNegativeButton("No", dialogClickListener).show();
	        	}else{
	        	Intent i = new Intent(getApplicationContext(), WelcomeScreen.class);
				i.putExtra("Action", "New Profile");
				if (i.resolveActivity(getPackageManager()) != null) {
				    startActivity(i);
				}
				this.finish();
	        }
	        	return true;
	 
	       
	        }else{
	        	return false;
	        	}
	    }  
	 public void writeString(File f, String[] data) throws IOException{
		 
		 FileOutputStream writer = new FileOutputStream(f,false);
	for (String string: data){
			 if (string != null){
		     writer.write(string.getBytes());
		     writer.write("\n".getBytes());
		     writer.flush();
			 }
		 }

		 writer.close();
	 }
	 
	 public void writeDoub(File f, double[][] data, int i) throws IOException{
		 
		 FileOutputStream writer = new FileOutputStream(f, false);
		
		 for (Double d: data[i]){
			 if (d != 0){
		     writer.write(String.valueOf(d.toString()).getBytes());
		     writer.write("\n".getBytes());
		     writer.flush();
			 }
		 }

		 writer.close();
	 }
	 public String[] gptograde(double[][] grade){
			 String[] ans = new String[10];
		 for (int i=0; i<10;i++){
			 if (grade[0][i] == 4){
				 ans[i] = "A";
			 }else if(grade[0][i] == 3.7){
				 ans[i] = "A-";
			 } else if(grade[0][i] == 3.33){
				 ans[i] = "B+";
			 }else if(grade[0][i] == 3){
				 ans[i] = "B";
			 }else if(grade[0][i] == 2.7){
				 ans[i] = "B-";
			 }else if(grade[0][i] == 2.30){
				 ans[i] = "C+";
			 }else if(grade[0][i] == 2){
				 ans[i] = "C";
			 }else if(grade[0][i] == 1.7){
				 ans[i] = "C-";
			 }else if(grade[0][i] == 1.3){
				 ans[i] = "D+";
			 }else if(grade[0][i] == 1){
				 ans[i] = "D";
			 }else if(grade[0][i] == .7){
				 ans[i] = "D-";
			 }else if(grade[0][i] == 0){
				 ans[i] = "F";
			 }
		 }
		 return ans;
		 }
	 public void Save() throws IOException{
		 
		String name = Cu_profile.getString("Profile_Name", "");
		File f;
		f =  new File(getApplicationInfo().dataDir + "/Profiles/" + name + "/Fall/Classes");
		writeString(f, gpaFall.classes);
		f = new File(getApplicationInfo().dataDir + "/Profiles/" + name + "/Fall/CreditHours");
		writeDoub(f, gpaFall.gparray, 1);
		f = new File(getApplicationInfo().dataDir + "/Profiles/" + name + "/Fall/Grades");
		writeString(f, gptograde(gpaFall.gparray));
		
		
		f = new File(getApplicationInfo().dataDir + "/Profiles/" + name + "/Spring/Classes");
		writeString(f, gpaSpring.classes);
		f = new File(getApplicationInfo().dataDir + "/Profiles/" + name + "/Spring/CreditHours");
		writeDoub(f, gpaSpring.gparray, 1);
		f = new File(getApplicationInfo().dataDir + "/Profiles/" + name + "/Spring/Grades");
		writeString(f, gptograde(gpaSpring.gparray));
		
		
		if(Cu_profile.getString("Mester", "").toString().equalsIgnoreCase("Quarter")){
			////Save Winter
			f = new File(getApplicationInfo().dataDir + "/Profiles/" + name + "/Winter/Classes");
			writeString(f, gpaWinter.classes);
			f = new File(getApplicationInfo().dataDir + "/Profiles/" + name + "/Winter/CreditHours");
			writeDoub(f, gpaWinter.gparray, 1);
			f = new File(getApplicationInfo().dataDir + "/Profiles/" + name + "/Winter/Grades");
			writeString(f, gptograde(gpaWinter.gparray));
		}
		
		 
		 
		 
	 }
	 
	 public void deleteprofile() throws IOException{//TODO Delete profile
		
		int d = settings.getInt("LastLoaded", 0);
		 String del = "profile_" + String.valueOf(d);
		 editor = settings.edit();
		 String badf;
			File[] current = new File(getApplicationInfo().dataDir + "/shared_prefs").listFiles();
			
			if (current.length <= 2){///if there is only one profile
				//TODO start Intent to new profile creation
				Cu_profile = this.getSharedPreferences("profile_0", 0);
				badf = Cu_profile.getString("Profile_Name", "");
				Cu_profile = this.getSharedPreferences("temp", 0);
				new File(getApplicationInfo().dataDir + "/Profiles/" + badf).delete();
				for (File f: current){
					if(!f.getName().substring(0, f.getName().lastIndexOf(".")).equals("data")){
						f.delete();
				}
					}
				this.recreate();
				
			}else{
			for (File f: current){
				if (f.getName().substring(0, f.getName().lastIndexOf(".")).equals(del)){
					Cu_profile = this.getSharedPreferences(f.getName().substring(0, f.getName().lastIndexOf(".")), 0);
					badf = Cu_profile.getString("Profile_Name", "");
					Cu_profile = this.getSharedPreferences("temp", 0);
					new File(getApplicationInfo().dataDir + "/Profiles/" + badf).delete();
					f.delete();
					editor.putInt("LastLoaded", 0);
				}
				}
				
			}
			File[] done = new File(getApplicationInfo().dataDir + "/shared_prefs").listFiles();
			
			for(int i=0;i<done.length;i++){
				File s = new File(getApplicationInfo().dataDir + "/shared_prefs/profile_" + String.valueOf(i) + ".xml");
				done[i].renameTo(s);
				
			}

			LoadProfile(0);
	 }
	 
	 public void Load() throws IOException{
		 String name = Cu_profile.getString("Profile_Name", "");
			File f;
			String[][] Classes = new String[3][10];
			String[][] Credits = new String[3][10];
			String[][] Grades = new String[3][10];
			String[] m = {"FALL", "SPRING", "WINTER"};
			
			f =  new File(getApplicationInfo().dataDir + "/Profiles/" + name + "/Fall/Classes");
			Classes[0] = readString(f);
			f = new File(getApplicationInfo().dataDir + "/Profiles/" + name + "/Fall/CreditHours");
			Credits[0] = readString(f);
			f = new File(getApplicationInfo().dataDir + "/Profiles/" + name + "/Fall/Grades");
			Grades[0] = readString(f);
			
			f = new File(getApplicationInfo().dataDir + "/Profiles/" + name + "/Spring/Classes");
			Classes[1] = readString(f);
			f = new File(getApplicationInfo().dataDir + "/Profiles/" + name + "/Spring/CreditHours");
			Credits[1] = readString(f);
			f = new File(getApplicationInfo().dataDir + "/Profiles/" + name + "/Spring/Grades");
			Grades[1] = readString(f);
			
			
			if(Cu_profile.getString("Mester", "").toString().equalsIgnoreCase("Quarter")){
				
				f = new File(getApplicationInfo().dataDir + "/Profiles/" + name + "/Winter/Classes");
				Classes[2] = readString(f);
				f = new File(getApplicationInfo().dataDir + "/Profiles/" + name + "/Winter/CreditHours");
				Credits[2] = readString(f);
				f = new File(getApplicationInfo().dataDir + "/Profiles/" + name + "/Winter/Grades");
				Grades[2] = readString(f);
			}
			
			for (int i=0; i<3;i++){ //run 3 times for three quarters
					for (int j=0;j<10;j++){
						if(j < Classes[i].length){
							if (!(Classes[i][j] == null)){
								LoadclassAdd(Classes[i][j], Credits[i][j], Grades[i][j], m[i]);
							}else{
								break;
							}
						}else{
							break;
						}
						}
					}
			
			
			updateGPA();
	 }

	 public void LoadclassAdd(String name, String credits, String grade, String Mester){
		 ToluLayout T = new ToluLayout();
		 int i;
			LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT));
			params.setMargins(0,0,0,3);
			
			
			if (Mester.equals("FALL")){
		i =  FallClasses.size();
					FallClasses.add(T.NewClass(name,
							credits, grade));
					Fall.addView(FallClasses.get(i), params);
					
					gpaFall.addGrade(Double.parseDouble(credits), grade,
							name);
				
				
			}else if (Mester.equals("WINTER")){
				i = WinterClasses.size();
						WinterClasses.add(T.NewClass(name,
								credits, grade));
						
						Winter.addView(WinterClasses.get(i), params);
						gpaWinter.addGrade(Double.parseDouble(credits), grade, 
								name);
					
			}else if (Mester.equals("SPRING")){
				i = SpringClasses.size();
						SpringClasses.add(T.NewClass(name,
								credits, grade));
						
						Spring.addView(SpringClasses.get(i), params);
						gpaSpring.addGrade(Double.parseDouble(credits), grade, 
								name);
					
			}
			
	 }
	 
 public String[] readString(File f) throws IOException{
	 
	 
	Scanner myfile = new Scanner(f);
		 List<String> tokens = new ArrayList<String>();
		 while (myfile.hasNext()) {
		     tokens.add(myfile.nextLine());
		 }
		 String[] data = tokens.toArray(new String[0]);

	 return data;
 }
	 
	 public void Clear(){
	 FallClasses = new ArrayList<LinearLayout>(); gpaFall = new GPA();
	 SpringClasses = new ArrayList<LinearLayout>(); gpaSpring = new GPA();
	 WinterClasses = new ArrayList<LinearLayout>(); gpaWinter = new GPA();
	 
	 ViewFlipper doubleL = (ViewFlipper) findViewById(R.id.view_flipper);

	 if(doubleL.getChildCount() > 0) {
		    doubleL.removeAllViews(); 
	 }
	 //Fall.removeAllViews(); Spring.removeAllViews(); Winter.removeAllViews();
	 Fall = new LinearLayout(this); Spring = new LinearLayout(this); Winter = new LinearLayout(this);

	 }
	
	public void onTest(View v){
		GPA myG = new GPA();
		myG.addGrade(4, "A-", "Math");
		
		Toast.makeText(getApplicationContext(), String.valueOf( myG.getGPA()), Toast.LENGTH_SHORT).show();
		
		
		
	}
	
	DialogInterface.OnClickListener dialogClickListener = new DialogInterface.OnClickListener() {
	    @Override
	    public void onClick(DialogInterface dialog, int which) {
	        switch (which){
	        case DialogInterface.BUTTON_POSITIVE:
	        	try{
	        	Save();
	        	Toast.makeText(getApplicationContext(), "Saved", Toast.LENGTH_SHORT).show();
	        	Intent i = new Intent(getApplicationContext(), WelcomeScreen.class);
				i.putExtra("Action", "New Profile");
				if (i.resolveActivity(getPackageManager()) != null) {
				    startActivity(i);
				}
				} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				Toast.makeText(getApplicationContext(), "Save Unsuccessful", Toast.LENGTH_SHORT).show();
				}
	            break;

	        case DialogInterface.BUTTON_NEGATIVE:
	        	Intent i = new Intent(getApplicationContext(), WelcomeScreen.class);
				i.putExtra("Action", "New Profile");
				if (i.resolveActivity(getPackageManager()) != null) {
				    startActivity(i);
				}
	            break;
	        }
	    }
	};

	DialogInterface.OnClickListener dragondeese = new DialogInterface.OnClickListener() {
	    @Override
	    public void onClick(DialogInterface dialog, int which) {
	        switch (which){
	        case DialogInterface.BUTTON_POSITIVE:
	        	try {
					deleteprofile();
					Toast.makeText(getApplicationContext(), "Delete Sucessful", Toast.LENGTH_SHORT).show();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
					Toast.makeText(getApplicationContext(), "Delete Unsucessful", Toast.LENGTH_SHORT).show();
				}
			
				}
	    }
	};
	

	// This defines your touch listener
	private final class MyTouchListener implements OnTouchListener {
	  public boolean onTouch(View view, MotionEvent motionEvent) {
	    if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
	      ClipData data = ClipData.newPlainText("", "");
	      DragShadowBuilder shadowBuilder = new View.DragShadowBuilder(view);
	      view.startDrag(data, shadowBuilder, view, 0);
	      view.setVisibility(View.GONE);
	      return true;
	    } else {
	    return false;
	    }
	  }
	} 
	

	private final class MyLClickListener implements OnLongClickListener {

	    @Override
	    public boolean onLongClick(View v) {
	          v.setVisibility(View.GONE);
	          return true;
	         
	    }

	}
	



	class ToluLayout{
		
		LinearLayout NewClass(String name, String units, String grade){
		
			LinearLayout BB = new LinearLayout(getApplicationContext());
			BB.setOrientation(LinearLayout.HORIZONTAL);
			BB.setLayoutParams(new LinearLayout.LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT, 1));
			BB.setGravity(Gravity.CENTER);
			BB.setWeightSum(1);
			TextView tv_name = new TextView(MainActivity.this);
			TextView tv_units = new TextView(MainActivity.this);
			TextView tv_grade = new TextView(MainActivity.this);
			tv_name.setLayoutParams(new LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT ));
			tv_name.setTextAppearance(MainActivity.this, android.R.style.TextAppearance_Large);
			tv_units.setLayoutParams(new LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT ));
			tv_units.setTextAppearance(MainActivity.this, android.R.style.TextAppearance_Large);
			tv_grade.setLayoutParams(new LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT ));
			tv_grade.setTextAppearance(MainActivity.this, android.R.style.TextAppearance_Large);
			
			tv_name.setTextColor(Color.parseColor("#FFFFFF"));
			tv_units.setTextColor(Color.parseColor("#FFFFFF"));
			tv_grade.setTextColor(Color.parseColor("#FFFFFF"));
			
			tv_name.setText(name); tv_name.setMinimumWidth(150);
			tv_units.setText("\t" + "(" + units + ")"); tv_units.setMinimumWidth(50);
			tv_grade.setText("\t" + grade);
			
			BB.setBackgroundResource(R.drawable.c_border);
			
			BB.addView(tv_name);
			BB.addView(tv_units);
			BB.addView(tv_grade);
			
			//BB.setOnTouchListener(new MyTouchListener());
		//	BB.setOnLongClickListener(new MyLClickListener()); //This one is ready to work!
			
			return BB;
			
		}
		
		LinearLayout NewQuarter(String Name){
		
		LinearLayout AA = new LinearLayout(MainActivity.this);
		FrameLayout Aa = new FrameLayout(MainActivity.this);
		TextView Ab = new TextView(MainActivity.this);
		//Set Properties
		AA.setOrientation(LinearLayout.VERTICAL);
		AA.setLayoutParams(new LinearLayout.LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT));
		AA.setGravity(Gravity.TOP);
		Aa.setLayoutParams(new FrameLayout.LayoutParams(LayoutParams.MATCH_PARENT,LayoutParams.WRAP_CONTENT ));
	
		Ab.setLayoutParams(new LayoutParams(LayoutParams.WRAP_CONTENT,LayoutParams.WRAP_CONTENT ));
		Ab.setTextAppearance(getApplicationContext(), android.R.style.TextAppearance_Large);
		Ab.setGravity(Gravity.CENTER);
		Ab.setText(Name);
		Ab.setMinWidth(100);
		Ab.setTextColor(Color.BLACK);
		Aa.addView(Ab);
		
		//AA.setOnDragListener();
		
		AA.addView(Aa);
		return AA;
		}
	}
	
	
	
	public void onClassAdd(View view){
		
		ToluLayout T = new ToluLayout();
		int i;
		EditText myclass = (EditText) findViewById(R.id.classname);
		Spinner mygrade = (Spinner) findViewById(R.id.grade);
		Spinner mycredits = (Spinner) findViewById(R.id.credit);
		LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT));
		params.setMargins(0,0,0,3);
		
		RadioGroup rg3 = (RadioGroup) findViewById(R.id.RG3);
		RadioButton rb = (RadioButton) findViewById(rg3.getCheckedRadioButtonId());
		
	if (myclass.getText().toString().equals("")){	
		Toast.makeText(getApplicationContext(), "Enter a class name.", Toast.LENGTH_SHORT).show();
	}else if (new String(myclass.getText().toString()).matches("[a-zA-Z_0-9 ]+") != true){
		Toast.makeText(getApplicationContext(),"Only numbers, alphabets and spaces are permitted.", Toast.LENGTH_SHORT).show();
		
	}else{
		
		if (rb.getText().toString().equals("FALL")){
			i = FallClasses.size();
			
			if (i == 10){
			Toast.makeText(getApplicationContext(), "Limit: 10 classes each.",
				   Toast.LENGTH_LONG).show();
			}else{
				FallClasses.add(T.NewClass(myclass.getText().toString(),
						mycredits.getSelectedItem().toString(), mygrade.getSelectedItem().toString()));
				Fall.addView(FallClasses.get(i), params);
				
				gpaFall.addGrade(Double.parseDouble(mycredits.getSelectedItem().toString()), mygrade.getSelectedItem().toString(),
						myclass.getText().toString());
			}
			
		}else if (rb.getText().toString().equals("WINTER")){
			i = WinterClasses.size();
			if (i == 10){
				Toast.makeText(getApplicationContext(), "Limit: 10 classes each.",
					   Toast.LENGTH_LONG).show();
				}else{
					WinterClasses.add(T.NewClass(myclass.getText().toString(),
							mycredits.getSelectedItem().toString(), mygrade.getSelectedItem().toString()));
					
					Winter.addView(WinterClasses.get(i), params);
					gpaWinter.addGrade(Double.parseDouble(mycredits.getSelectedItem().toString()), mygrade.getSelectedItem().toString(), 
							myclass.getText().toString());
				}
		}else if (rb.getText().toString().equals("SPRING")){
			i = SpringClasses.size();
			if (i == 10){
				Toast.makeText(getApplicationContext(), "Limit: 10 classes each.",
					   Toast.LENGTH_LONG).show();
				}else{
					SpringClasses.add(T.NewClass(myclass.getText().toString(),
							mycredits.getSelectedItem().toString(), mygrade.getSelectedItem().toString()));
					
					Spring.addView(SpringClasses.get(i), params);
					gpaSpring.addGrade(Double.parseDouble(mycredits.getSelectedItem().toString()), mygrade.getSelectedItem().toString(), 
							myclass.getText().toString());
				}
		}
		updateGPA();
		myclass.setText("");
		mygrade.setSelection(0);
		}
    
		
		
		}
		
	

	
; 
		

	
	
	

}


