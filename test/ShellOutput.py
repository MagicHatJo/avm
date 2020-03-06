import os
import sys
import threading
import time

class ShellOutput(object):
    escape_char = "\b"

    def __init__(self, stream=None, threaded=False):
        self.origstream = stream
        self.threaded = threaded
        if self.origstream is None:
            self.origstream = sys.stdout
        self.origstreamfd = self.origstream.fileno()
        self.capturedtext = ""
        self.pipe_out, self.pipe_in = os.pipe()

    def __enter__(self):
        self.start()
        return self

    def __exit__(self, type, value, traceback):
        self.stop()

    def start(self):
        self.capturedtext = ""
        self.streamfd = os.dup(self.origstreamfd)
        os.dup2(self.pipe_in, self.origstreamfd)
        if self.threaded:
            self.workerThread = threading.Thread(target=self.readOutput)
            self.workerThread.start()
            time.sleep(0.01)

    def stop(self):
        self.origstream.write(self.escape_char)
        self.origstream.flush()
        if self.threaded:
            self.workerThread.join()
        else:
            self.readOutput()
        os.close(self.pipe_in)
        os.close(self.pipe_out)
        os.dup2(self.streamfd, self.origstreamfd)
        os.close(self.streamfd)

    def readOutput(self):
        while True:
            char = os.read(self.pipe_out,1).decode(self.origstream.encoding)
            if not char or self.escape_char in char:
                break
            self.capturedtext += char