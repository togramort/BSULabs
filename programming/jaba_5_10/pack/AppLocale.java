package pack;

import java.util.Locale;
import java.util.ResourceBundle;

public class AppLocale {

		private static final String strMsg = "pack.Msg";
		private static Locale loc = Locale.getDefault();
		private static ResourceBundle res = 
				ResourceBundle.getBundle( AppLocale.strMsg, AppLocale.loc );
		
		static Locale get() {
			return AppLocale.loc;
		}
		
		static void set(Locale loc) {
			AppLocale.loc = loc;
			res = ResourceBundle.getBundle(AppLocale.strMsg, AppLocale.loc);
		}
		
		static ResourceBundle getBundle() {
			return AppLocale.res;
		}
		
		static String getString(String key) {
			return AppLocale.res.getString(key);
		}
		
		// Resource keys:
		
		public static final String name = "name";
		public static final String age = "age";
		public static final String education = "education";
		public static final String masters = "masters";
		public static final String bachelors = "bachelors";
		public static final String secondary = "secondary";
		public static final String general = "general";
		public static final String none = "none";
		public static final String cool_game_company = "cool_game_company";
		public static final String exp = "exp";
		public static final String time = "time";
}