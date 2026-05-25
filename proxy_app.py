def main():
    driver_handle = open('/proc/sharvin_driver')
    kern_space_msg = driver_handle.readline()
    print(kern_space_msg)
    driver_handle.close()
    return

main()