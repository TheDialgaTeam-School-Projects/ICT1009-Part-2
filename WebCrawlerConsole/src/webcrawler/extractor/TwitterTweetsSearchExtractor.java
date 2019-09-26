package webcrawler.extractor;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.reflect.TypeToken;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
import webcrawler.Extractor;
import webcrawler.data.TwitterSearchData;
import webcrawler.data.TwitterTweetData;

import java.io.*;
import java.net.URL;
import java.net.URLConnection;
import java.nio.file.FileSystems;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class TwitterTweetsSearchExtractor extends Extractor<TwitterTweetData> {

    private final String cacheFileLocation = FileSystems.getDefault().getPath("TwitterSearchData.json").toString();

    @Override
    public List<TwitterTweetData> getData(boolean ignoreCache) {
        if (!ignoreCache) {
            Gson gson = new GsonBuilder().setPrettyPrinting().create();

            File file = new File(cacheFileLocation);

            if (file.exists()) {
                try (FileReader fileReader = new FileReader(file)) {
                    return gson.fromJson(fileReader, new TypeToken<List<TwitterTweetData>>() {
                    }.getType());
                } catch (IOException ignored) {
                }
            }
        }

        ArrayList<TwitterTweetData> twitterTweetDataArrayList = new ArrayList<>();

        TwitterSearchData twitterSearchData = null;

        System.out.println("Downloading Twitter Page...");

        for (int i = 0; i < 60; i++) {
            if (twitterSearchData == null)
                twitterSearchData = getTwitterSearchData();
            else
                twitterSearchData = getTwitterSearchData(twitterSearchData.getMinPosition());

            System.out.println("Progress: " + (i + 1) + " / " + 60);

            if (twitterSearchData == null)
                continue;

            Document document = Jsoup.parseBodyFragment(twitterSearchData.getItemsHtml());
            Elements tweetElements = document.select("div.tweet");

            for (Element tweetElement : tweetElements) {
                try {
                    TwitterTweetData twitterTweetData = new TwitterTweetData();
                    twitterTweetData.setTweetId(Long.parseLong(tweetElement.attr("data-tweet-id")));
                    twitterTweetData.setTweetAuthor(tweetElement.attr("data-screen-name"));
                    twitterTweetData.setTweetMessage(tweetElement.select("p.tweet-text").text());
                    twitterTweetData.setTweetTimestamp(new Date(Long.parseLong(tweetElement.select("span.js-short-timestamp").attr("data-time-ms"))));

                    String service = "";
                    Pattern p = Pattern.compile("(?=.*([Nn][Ss][Ll])).*");
                    Pattern p1 = Pattern.compile("(?=.*([Ee][Ww][Ll])).*");
                    Pattern p2 = Pattern.compile("(?=.*([Nn][Ee][Ll])).*");
                    Pattern p3 = Pattern.compile("(?=.*([Dd][Tt][Ll])).*");
                    Pattern p4 = Pattern.compile("(?=.*([Cc][Cc][Ll])).*");
                    Pattern p5 = Pattern.compile("(?=.*([Bb][Pp][Ll][Rr][Tt])).*");
                    Pattern p6 = Pattern.compile("\\[(.*?)\\]");
                    Pattern[] pArr = new Pattern[]{p, p1, p2, p3, p4, p5, p6};

                    for (int j = 0; j < 6; j++) {
                        Matcher M = pArr[j].matcher(tweetElement.select("p.tweet-text").text());
                        if (M.find()) {
                            service = M.group(1);
                            service = service.split("\\s")[0];
                            break;
                        }
                    }
                    switch (service) {
                        case "EWL":
                            service = "East-West Line";
                            break;
                        case "NSL":
                            service = "North-South Line";
                            break;
                        case "NEL":
                            service = "North-East Line";
                            break;
                        case "CCL":
                            service = "Circle Line";
                            break;
                        case "DTL":
                            service = "Downtown Line";
                            break;
                        case "BPLRT":
                            service = "Bukit Panjang LRT";
                            break;
                        default:
                            service = "";
                            break;
                    }
                    twitterTweetData.setTweetTrainLine(service);

                    twitterTweetDataArrayList.add(twitterTweetData);
                } catch (NumberFormatException ignored) {
                }
            }
        }

        System.out.println("Download completed!");

        saveIntoCache(cacheFileLocation, twitterTweetDataArrayList);

        return twitterTweetDataArrayList;
    }

    private TwitterSearchData getTwitterSearchData() {
        return getTwitterSearchData(null);
    }

    private TwitterSearchData getTwitterSearchData(String position) {
        if (position == null)
            position = "";

        try {
            URL url = new URL("https://twitter.com/i/search/timeline?l=en&f=tweets&q=from%3ASMRT_Singapore&src=typed&max_position=" + position);
            URLConnection connection = url.openConnection();
            connection.setRequestProperty("User-Agent", generateRandomUserAgent());

            try (BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(connection.getInputStream()))) {
                Gson gson = new GsonBuilder().setPrettyPrinting().create();
                return gson.fromJson(bufferedReader, TwitterSearchData.class);
            } catch (IOException ignored) {
            }
        } catch (IOException ignored) {
        }

        return null;
    }

    private String generateRandomUserAgent() {
        // Disclaimer: This line of code is an ugly way to avoid blocking firefox browser from accessing twitter due to
        // recent patch on 20 Feb 2019.

        // Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:65.0) Gecko/20100101 Firefox/65.0
        // As a result, the scrapper code will only run once and that's pretty much it.

        // The following algorithm will generate a random string that will avoid blocking actual browser and won't affect
        // other group scraping similar data from twitter.

        // This randomizer will fix this issue for a while but it may not last long.
        StringBuilder stringBuilder = new StringBuilder();
        Random random = new Random();

        for (int i = 0; i < 30; i++) {
            // This generate a random 30 characters of random characters.
            stringBuilder.append((char) ('0' + random.nextInt('z' - '0' + 2)));
        }
        return stringBuilder.toString();
    }
}
