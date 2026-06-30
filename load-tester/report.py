import csv
import os

REPORT_DIR = "reports"

os.makedirs(REPORT_DIR, exist_ok=True)

def save_report(clients,
                success,
                failed,
                total_requests,
                avg_latency,
                max_latency,
                execution_time):

    from datetime import datetime

    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")

    filename = os.path.join(
        REPORT_DIR,
        f"load_test_{timestamp}.csv"
    )
    

    with open(filename, "w", newline="") as file:

        writer = csv.writer(file)

        writer.writerow(["Metric", "Value"])
        writer.writerow(["Clients", clients])
        writer.writerow(["Successful Clients", success])
        writer.writerow(["Failed Clients", failed])
        writer.writerow(["Total Requests", total_requests])
        writer.writerow(["Average Latency (ms)", round(avg_latency, 2)])
        writer.writerow(["Maximum Latency (ms)", round(max_latency, 2)])
        writer.writerow(["Execution Time (sec)", round(execution_time, 2)])

    print(f"\nCSV report saved to: {filename}")