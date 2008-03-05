
static getString(addr)
{
  auto origa, stringRead;

  stringRead = "";
  origa = addr;

  while(1)
  {
      if (Byte(addr) == 0) break;
      if (addr-origa > 40) return "";
      
      stringRead = form("%s%c", stringRead, Byte(addr));

      addr = addr + 1;
  }

  return stringRead;
}
