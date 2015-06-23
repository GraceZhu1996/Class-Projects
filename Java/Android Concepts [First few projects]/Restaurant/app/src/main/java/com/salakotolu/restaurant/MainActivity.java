package com.salakotolu.restaurant;

import android.app.ActionBar;
import android.app.Activity;
import android.app.Fragment;
import android.app.FragmentManager;
import android.graphics.Typeface;
import android.os.Bundle;
import android.os.Handler;
import android.support.v4.widget.DrawerLayout;
import android.text.TextUtils;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;

import java.text.NumberFormat;
import java.util.Map;


public class MainActivity extends Activity
        implements NavigationDrawerFragment.NavigationDrawerCallbacks {

    /**
     * Fragment managing the behaviors, interactions and presentation of the navigation drawer.
     */
    private NavigationDrawerFragment mNavigationDrawerFragment;

    /**
     * Used to store the last screen title. For use in {@link #restoreActionBar()}.
     */
    private CharSequence mTitle;

    private Handler handler = new Handler();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mNavigationDrawerFragment = (NavigationDrawerFragment)
                getFragmentManager().findFragmentById(R.id.navigation_drawer);
        mTitle = getTitle();

        // Set up the drawer.
        mNavigationDrawerFragment.setUp(
                R.id.navigation_drawer,
                (DrawerLayout) findViewById(R.id.drawer_layout));


           updateTray.run();
        //updateTray();
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
        Data.drawer_position = number -1;
        mTitle = Data.drawer_names[number -1];


            //Check if menus have been created
            menu_page menu= new menu_page();

            getFragmentManager().beginTransaction().
                    replace(R.id.container, menu).commit();
        //updateTray();

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
            getMenuInflater().inflate(R.menu.main, menu);
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

        @Override
        public View onCreateView(LayoutInflater inflater, ViewGroup container,
                Bundle savedInstanceState) {
            View rootView = inflater.inflate(R.layout.fragment_main, container, false);
            return rootView;
        }

        @Override
        public void onAttach(Activity activity) {
            super.onAttach(activity);
            ((MainActivity) activity).onSectionAttached(
                    getArguments().getInt(ARG_SECTION_NUMBER));
        }
    }


    public Runnable updateTray = new Runnable() {
        @Override
        public void run() {

            LinearLayout tray = (LinearLayout) findViewById(R.id.tray);
            TextView tv_total = (TextView) findViewById(R.id.total);

            NumberFormat currency = NumberFormat.getCurrencyInstance();

            try {
                tray.removeAllViews();
            }catch (Exception e){

            }

            double _total = 0;

            for (Map<String, String> foodItem : Data.tray){
                LinearLayout order, order_top, order_bottom;
                order = new LinearLayout(MainActivity.this); order_top = new LinearLayout(MainActivity.this); order_bottom = new LinearLayout(MainActivity.this);
                order.setOrientation(LinearLayout.VERTICAL);
                order_bottom.setOrientation(LinearLayout.HORIZONTAL);
                order_bottom.setGravity(Gravity.CENTER_HORIZONTAL);
                order_top.setOrientation(LinearLayout.HORIZONTAL);
                order_top.setGravity(Gravity.CENTER_HORIZONTAL);

                TextView name, price, quantity, total; //EditText quantity_edit = new EditText(this);
                name = new TextView(MainActivity.this); price = new TextView(MainActivity.this);
                quantity = new TextView(MainActivity.this); total = new TextView(MainActivity.this);

                name.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT, 1f));
                price.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT, 1f));
                quantity.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT, 1f));
                total.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT, 1f));



                name.setText(foodItem.get("name"));
                name.setEllipsize(TextUtils.TruncateAt.END);
                name.setTypeface(Typeface.DEFAULT_BOLD);
                price.setText(currency.format(Double.valueOf(foodItem.get("price"))));
                price.setTypeface(Typeface.DEFAULT_BOLD);
                quantity.setText("Qty: " + foodItem.get("quantity"));
            /*quantity_edit.setText(foodItem.get("quantity"));

            quantity_edit.setInputType(InputType.TYPE_CLASS_NUMBER);
            quantity_edit.setMaxEms(3);
            quantity_edit.setMaxLines(1);
            quantity_edit.setFilters(new InputFilter[] { new InputFilter.LengthFilter(3) });*/
                double __total = Double.valueOf(foodItem.get("price"))*Integer.valueOf(foodItem.get("quantity"));
                total.setText(currency.format(__total));


                name.setGravity(Gravity.LEFT); price.setGravity(Gravity.RIGHT);
                quantity.setGravity(Gravity.LEFT); total.setGravity(Gravity.RIGHT);

                order_top.addView(name);
                order_top.addView(price);
                order_bottom.addView(quantity); order_bottom.addView(total);

                order.addView(order_top); order.addView(order_bottom);

                _total += __total;
                tray.addView(order);
            }

            tv_total.setText(currency.format(_total));

            handler.postDelayed(this, 400);
        }

    };


}