import numpy
import torch as torch
import logging

logger = logging.getLogger(__name__)
logger.setLevel(logging.DEBUG)
ch = logging.StreamHandler()
ch.setLevel(logging.DEBUG)
formatter = logging.Formatter('%(asctime)s %(name)s %(levelname)s %(message)s')
ch.setFormatter(formatter)
logger.addHandler(ch)

assert torch.cuda.is_available()
logger.info("Availabled devices %s", torch.cuda.device_count())

cuda = torch.device('cuda')

x = torch.tensor([1., 2.], device=cuda)
y = torch.tensor([1., 2.]).cuda()

with torch.cuda.device(0):
    a = torch.tensor([1., 2.], device=cuda)
    b = torch.tensor([1., 2.]).cuda()
    b2 = torch.tensor([1., 2.]).to(device=cuda)
    c = a + b
    z = x + y

    d = torch.randn(2, device=cuda)
    e = torch.randn(2).to(cuda)
    f = torch.randn(2).cuda(cuda)

if __name__ == '__main__':
    pass