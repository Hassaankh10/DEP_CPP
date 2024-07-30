#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <algorithm>
#include <exception>

using namespace std;

class GeoLocation
{
public:
    string placeName;
    double lat;
    double lon;

    GeoLocation(const string &placeName, double lat, double lon)
        : placeName(placeName), lat(lat), lon(lon) {}
};

class GeoLocationManager
{
private:
    vector<GeoLocation> geoLocations;

public:
    void insertLocation(const string &placeName, double lat, double lon)
    {
        geoLocations.push_back(GeoLocation(placeName, lat, lon));
    }

    void deleteLocation(const string &placeName)
    {
        geoLocations.erase(remove_if(geoLocations.begin(), geoLocations.end(),
                                     [&placeName](const GeoLocation &location)
                                     { return location.placeName == placeName; }),
                           geoLocations.end());
    }

    void displayLocations() const
    {
        for (const auto &location : geoLocations)
        {
            cout << "Name: " << location.placeName << ", Latitude: " << location.lat << ", Longitude: " << location.lon << endl;
        }
    }
};

class WeatherMetric
{
public:
    string metricName;
    double metricValue;

    WeatherMetric(const string &metricName, double metricValue)
        : metricName(metricName), metricValue(metricValue) {}
};

class WeatherMetricManager
{
private:
    vector<WeatherMetric> metrics;

public:
    void addMetric(const string &metricName, double metricValue)
    {
        metrics.push_back(WeatherMetric(metricName, metricValue));
    }

    void removeMetric(const string &metricName)
    {
        metrics.erase(remove_if(metrics.begin(), metrics.end(),
                                [&metricName](const WeatherMetric &metric)
                                { return metric.metricName == metricName; }),
                      metrics.end());
    }

    void listMetrics() const
    {
        for (const auto &metric : metrics)
        {
            cout << "Metric: " << metric.metricName << ", Value: " << metric.metricValue << endl;
        }
    }
};

class WeatherService
{
protected:
    string apiKey;
    string apiBaseUrl;

public:
    WeatherService(const string &apiKey, const string &apiBaseUrl)
        : apiKey(apiKey), apiBaseUrl(apiBaseUrl) {}

    virtual string getApiResponse(const string &endpoint, const map<string, string> &params)
    {
        return "API response data"; 
    }

    virtual void processApiResponse(const string &response) = 0; // Pure virtual function
};

class ForecastService : public WeatherService
{
public:
    ForecastService(const string &apiKey, const string &apiBaseUrl)
        : WeatherService(apiKey, apiBaseUrl) {}

    string getForecast(const GeoLocation &location)
    {
        return "Forecast data"; 
    }

    void processApiResponse(const string &response) override
    {
        cout << response << endl;
    }
};

class HistoricalWeatherService : public WeatherService
{
public:
    HistoricalWeatherService(const string &apiKey, const string &apiBaseUrl)
        : WeatherService(apiKey, apiBaseUrl) {}

    string getHistoricalData(const GeoLocation &location, const string &start, const string &end)
    {
        return "Historical weather data"; 
    }

    void processApiResponse(const string &response) override
    {
        cout << response << endl;
    }
};

class DataSaver
{
public:
    static void saveToCSV(const string &data, const string &file)
    {
        ofstream outFile(file);
        outFile << data;
        outFile.close();
    }

    static void saveToJSON(const string &data, const string &file)
    {
        ofstream outFile(file);
        outFile << data;
        outFile.close();
    }
};

class CloudStorageService
{
private:
    string cloudCredentials;

public:
    CloudStorageService(const string &cloudCredentials)
        : cloudCredentials(cloudCredentials) {}

    // void uploadToCloud(const string &data)
    // {
    //     // Implement cloud saving functionality
    // }

    string downloadFromCloud(const string &filters)
    {
        return "Cloud data"; 
    }

    void saveLocally(const string &data)
    {
        ofstream outFile("local_data.txt");
        outFile << data;
        outFile.close();
    }

    string loadLocally(const string &filters)
    {
        ifstream inFile("local_data.txt");
        string data((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
        return data;
    }
};

class APIServiceClient
{
public:
    string requestData(const string &endpoint, const map<string, string> &params)
    {
        return "API response"; 
    }
};

class UserIO
{
public:
    string readUserInput()
    {
        string input;
        getline(cin, input);
        return input;
    }

    bool checkInput(const string &input)
    {
        return true; 
    }

    void displayError(const exception &error)
    {
        cerr << "Error: " << error.what() << endl;
    }
};

int main()
{
    GeoLocationManager geoLocationManager;
    WeatherMetricManager weatherMetricManager;
    ForecastService forecastService("api_key", "https://api.weather.com");
    HistoricalWeatherService historicalWeatherService("api_key", "https://api.weather.com");
    UserIO userIO;

    while (true)
    {
        cout << "Menu:\n";
        cout << "1. Add GeoLocation\n";
        cout << "2. Remove GeoLocation\n";
        cout << "3. List GeoLocations\n";
        cout << "4. Add Weather Metric\n";
        cout << "5. Remove Weather Metric\n";
        cout << "6. List Weather Metrics\n";
        cout << "7. Get Weather Forecast\n";
        cout << "8. Get Historical Weather Data\n";
        cout << "9. Save Data to CSV\n";
        cout << "10. Save Data to JSON\n";
        cout << "11. Exit\n";
        cout << "Enter choice: ";
        string choice = userIO.readUserInput();

        try
        {
            if (choice == "1")
            {
                cout << "Enter place name: ";
                string name = userIO.readUserInput();
                cout << "Enter latitude: ";
                double lat;
                cin >> lat;
                cout << "Enter longitude: ";
                double lon;
                cin >> lon;
                cin.ignore();
                geoLocationManager.insertLocation(name, lat, lon);
            }
            else if (choice == "2")
            {
                cout << "Enter place name to remove: ";
                string name = userIO.readUserInput();
                geoLocationManager.deleteLocation(name);
            }
            else if (choice == "3")
            {
                geoLocationManager.displayLocations();
            }
            else if (choice == "4")
            {
                cout << "Enter metric name: ";
                string metricName = userIO.readUserInput();
                cout << "Enter value: ";
                double value;
                cin >> value;
                cin.ignore();
                weatherMetricManager.addMetric(metricName, value);
            }
            else if (choice == "5")
            {
                cout << "Enter metric name to remove: ";
                string metricName = userIO.readUserInput();
                weatherMetricManager.removeMetric(metricName);
            }
            else if (choice == "6")
            {
                weatherMetricManager.listMetrics();
            }
            else if (choice == "7")
            {
                cout << "Enter place name for forecast: ";
                string locationName = userIO.readUserInput();
                GeoLocation location(locationName, 0.0, 0.0);
                string forecast = forecastService.getForecast(location);
                forecastService.processApiResponse(forecast);
            }
            else if (choice == "8")
            {
                cout << "Enter place name for historical data: ";
                string locationName = userIO.readUserInput();
                cout << "Enter start date (YYYY-MM-DD): ";
                string startDate = userIO.readUserInput();
                cout << "Enter end date (YYYY-MM-DD): ";
                string endDate = userIO.readUserInput();
                GeoLocation location(locationName, 0.0, 0.0);
                string historicalData = historicalWeatherService.getHistoricalData(location, startDate, endDate);
                historicalWeatherService.processApiResponse(historicalData);
            }
            else if (choice == "9")
            {
                cout << "Enter data to save: ";
                string data = userIO.readUserInput();
                cout << "Enter file name: ";
                string file = userIO.readUserInput();
                DataSaver::saveToCSV(data, file);
            }
            else if (choice == "10")
            {
                cout << "Enter data to save: ";
                string data = userIO.readUserInput();
                cout << "Enter file name: ";
                string file = userIO.readUserInput();
                DataSaver::saveToJSON(data, file);
            }
            else if (choice == "11")
            {
                break;
            }
            else
            {
                cout << "Invalid choice, please try again." << endl;
            }
        }
        catch (const exception &ex)
        {
            userIO.displayError(ex);
        }
    }

    return 0;
}
