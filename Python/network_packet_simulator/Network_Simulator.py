import Packet
import Buffer

def read_input(filename):
    """ Read the inputs from the file and return a list of packets. """

    buf_size = 0
    num_pkts = 0
    line_num = 1
    packets = []

    with open(filename, 'r') as file:
        for line in file:
            if line_num == 1:
                buf_size, num_pkts = (int(i) for i in line.split())
            else:
                arrival_time, process_time = (int(i) for i in line.split())
                pkt = Packet.Packet(arrival_time, process_time)
                packets.append(pkt)
            line_num += 1

    assert(num_pkts == len(packets))
    return [buf_size, num_pkts, packets]

def process_packets(buffer, packets):
    """ Process the incoming packets. """

    finish_time = 0 # Finish time of the last processed packet

    for i in range(len(packets)):
        pkt = packets[i]

        # Pop all packets from buffer whose finish time < new packet's
        # arrival time
        while not buffer.is_empty():
            if buffer.get_packet(0).get_finish_time() <= pkt.arrival_time:
                # Remove packet from front of the buffer
                tmp_pkt = buffer.pop()
                assert(tmp_pkt is not None)
            else:
                break

        # If buffer is full, drop the packet else push the packet in the buffer
        if buffer.is_full():
            pkt.drop()
        else:
            if buffer.is_empty():
                # First incoming packet
                pkt.start_time = pkt.arrival_time
            else:
                pkt.start_time = finish_time

            finish_time = pkt.get_finish_time()
            assert(buffer.append(pkt) == True)

    # Write packet start_time to output file
    with open('./output.txt', 'w') as file:
        for i in range(len(packets)):
            pkt = packets[i]
            if pkt.is_dropped():
                file.write('-1\n')
            else:
                file.write('%d\n' % pkt.start_time)

def main():
    # Read the inputs from the file
    buf_size, num_pkts, packets = read_input('./testcases.txt')

    # Create the packet buffer
    buffer = Buffer.Buffer(buf_size)

    # Process the packets
    process_packets(buffer, packets)

if __name__ == '__main__':
    main()
