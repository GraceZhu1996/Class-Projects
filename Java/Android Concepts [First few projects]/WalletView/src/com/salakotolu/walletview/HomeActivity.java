/*
 * Toluwanimi Salako 06/18/2014
 */
package com.salakotolu.walletview;

import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.List;

import android.annotation.SuppressLint;
import android.app.ActionBar;
import android.app.Activity;
import android.app.Fragment;
import android.app.FragmentManager;
import android.graphics.Color;
import android.graphics.Typeface;
import android.os.Bundle;
import android.support.v4.widget.DrawerLayout;
import android.text.TextUtils.TruncateAt;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

public class HomeActivity extends Activity
        implements NavigationDrawerFragment.NavigationDrawerCallbacks {
    /**
     * Fragment managing the behaviors, interactions and presentation of the navigation drawer.
     */
    private NavigationDrawerFragment mNavigationDrawerFragment;

    /**
     * Used to store the last screen title. For use in {@link #restoreActionBar()}.
     */
    private CharSequence mTitle;
   
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        setContentView(R.layout.activity_home);
        

        mNavigationDrawerFragment = (NavigationDrawerFragment)
                getFragmentManager().findFragmentById(R.id.navigation_drawer);
        mTitle = getTitle();

        // Set up the drawer.
        mNavigationDrawerFragment.setUp(
                R.id.navigation_drawer,
                (DrawerLayout) findViewById(R.id.drawer_layout));
    }

    @Override
    public void onNavigationDrawerItemSelected(int position) {
        // update the main content by replacing fragments
        FragmentManager fragmentManager = getFragmentManager();
        fragmentManager.beginTransaction()
                .replace(R.id.container, PlaceholderFragment.newInstance(position + 1))
                .commit();
    }

    public void onSectionAttached(int number) {
        switch (number) {
            case 1:
                mTitle = getString(R.string.title_section1);
                break;
            case 2:
                mTitle = getString(R.string.title_section2);
                break;
            case 3:
                mTitle = getString(R.string.title_section3);
                break;
        }
    }

    public void restoreActionBar() {
        ActionBar actionBar = getActionBar();
        actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_STANDARD);
        actionBar.setDisplayShowTitleEnabled(true);
        actionBar.setTitle(mTitle);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        if (!mNavigationDrawerFragment.isDrawerOpen()) {
            // Only show items in the action bar relevant to this screen
            // if the drawer is not showing. Otherwise, let the drawer
            // decide what to show in the action bar.
            getMenuInflater().inflate(R.menu.home, menu);
            restoreActionBar();
            return true;
        }
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    /**
     * A placeholder fragment containing a simple view.
     */
    public static class PlaceholderFragment extends Fragment {
        /**
         * The fragment argument representing the section number for this
         * fragment.
         */
        private static final String ARG_SECTION_NUMBER = "section_number";

        /**
         * Returns a new instance of this fragment for the given section
         * number.
         */
        public static PlaceholderFragment newInstance(int sectionNumber) {
            PlaceholderFragment fragment = new PlaceholderFragment();
            Bundle args = new Bundle();
            args.putInt(ARG_SECTION_NUMBER, sectionNumber);
            fragment.setArguments(args);
            return fragment;
        }

        public PlaceholderFragment() {
        }

		@SuppressLint("NewApi")
		@Override
        public View onCreateView(LayoutInflater inflater, ViewGroup container,
                Bundle savedInstanceState) {
            View rootView = inflater.inflate(R.layout.fragment_home, container, false);
            NumberFormat currency = NumberFormat.getCurrencyInstance();
            TextView money_left  = (TextView) rootView.findViewById(R.id.txt_amtleft);
            LinearLayout base = (LinearLayout) rootView.findViewById(R.id.base);
            
            //Creating and populating the amount left for each item.
            double money = 963.26; //Amount left
            
            money_left.setText(currency.format(money));
            money_left.setTextSize(40);
            money_left.setTypeface(Typeface.DEFAULT_BOLD);
            money_left.setMaxLines(1);
            money_left.setEllipsize(TruncateAt.END);
            
            if (money > 0){
            	money_left.setTextColor(Color.GREEN);
        	}else{
        		money_left.setTextColor(Color.RED);
        	} 
            
            TableLayout table = new TableLayout(rootView.getContext());
            table.setStretchAllColumns(true);
            table.setShrinkAllColumns(true);
            
            
            //For loop goes here
            WalletView main = ((WalletView) getActivity().getApplication());
            Data data = main.GetData();
            data.Setup();
            main.updateData(data);
            
            
            String[] cat = {"Food", "Enterntainment", "Shopping", "Eating", "Mortgage or rent", "Phone", "Electricity", "Gas", "Water and sewer", "Cable", "Waste removal",
            		"Maintenance or repairs", "Supplies"};
            double[] amt = {50.87, 800.989, 1000, -500, 89, 53, -99, -8880000000.00, 103.66, 805, 87.182, -36, 1230000};
            for (int i = 0; i< cat.length; i++){
            	TableRow row = new TableRow(rootView.getContext());
            	row.setGravity(Gravity.CENTER_HORIZONTAL);
            	TextView item = new TextView(rootView.getContext());
            	item.setText(cat[i]);
            	item.setGravity(Gravity.LEFT);
            	item.setPadding(3, 0, 0, 0);
            	item.setTextSize(20);
            	item.setMaxLines(1);
            	item.setEllipsize(TruncateAt.END);
            	TextView amount_left = new TextView(rootView.getContext());
            	amount_left.setTextSize(20);  
            	amount_left.setTypeface(Typeface.DEFAULT_BOLD);
            	amount_left.setMaxLines(1);
            	amount_left.setEllipsize(TruncateAt.END);
            	
            	//Used to differentiate between rows
            	row.setTag(i); 
            	//Format Price
            	amount_left.setText(currency.format((amt[i])));
            	
            	if (amt[i] > 0){
            		amount_left.setTextColor(Color.parseColor("#00FF00"));
            	}else{
            		amount_left.setTextColor(Color.RED);
            	}        	
            	
            	if (i%2 == 0){
            		row.setBackgroundColor(Color.parseColor("#001433"));
                	item.setTextColor(Color.parseColor("#FFFFFF"));
            	}else{
            		row.setBackgroundColor(Color.parseColor("#1975FF"));
                	item.setTextColor(Color.parseColor("#000000"));
            	}

            	amount_left.setGravity(Gravity.RIGHT);
            	amount_left.setPadding(0, 0, 3, 0);
            	row.addView(item);
            	row.addView(amount_left);
            	row.setPadding(0, 5, 0, 5);
            	table.addView(row);
            }
            base.addView(table);
            return rootView;
        }

        @Override
        public void onAttach(Activity activity) {
            super.onAttach(activity);
            ((HomeActivity) activity).onSectionAttached(
                    getArguments().getInt(ARG_SECTION_NUMBER));
        }
    }

}
