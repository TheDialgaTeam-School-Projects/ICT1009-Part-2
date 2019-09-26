package webcrawler;

import webcrawler.extractor.TrainServiceDisruptionSheetExtractor;
import webcrawler.extractor.TwitterTweetsSearchExtractor;

public class Main {

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("ERROR: Unknown Command Line.");
            return;
        }

        String action = args[0];

        System.out.println("==================================================");
        System.out.println("MRT Web Crawler - Downloading Data from the internet...");
        System.out.println("==================================================");
        System.out.println("PLEASE DO NOT CLOSE THIS WINDOW TO PREVENT DATA CORRUPTION!");
        System.out.println();

        if (action.contentEquals("TrainServiceDisruptionSheetExtractor")) {
            TrainServiceDisruptionSheetExtractor extractor = new TrainServiceDisruptionSheetExtractor();
            extractor.getData(true);
        }

        if (action.contentEquals("TwitterTweetsSearchExtractor")) {
            TwitterTweetsSearchExtractor extractor = new TwitterTweetsSearchExtractor();
            extractor.getData(true);
        }
    }
}
