
//**************************************************************************//
int getMaxMalloc(int min_mem, int max_mem)
{
  int prev_size = min_mem;
  int curr_size = min_mem;
  int max_free = 0;
  //  Serial.print("checkmem: testing alloc from ");
  //  Serial.print(min_mem);
  //  Serial.print(" : ");
  //  Serial.print(max_mem);
  //  Serial.println(" bytes");
  while (1)
  {
    void *foo1 = malloc(curr_size);
    if (foo1 == nullptr)
    { // Back off
      max_mem = std::min(curr_size, max_mem);
      curr_size = (int)(curr_size - (curr_size - prev_size) / 2.0);
    }
    else
    { // Advance
      free(foo1);
      max_free = curr_size;
      prev_size = curr_size;
      curr_size = std::min(curr_size * 2, max_mem);
    }
    if (abs(curr_size - prev_size) == 0)
    {
      break;
    }
  }
  //  Serial.print("checkmem: max free heap = ");
  //  Serial.print(esp_get_free_heap_size());
  //  Serial.print(" bytes, max allocable = ");
  //  Serial.print(max_free);
  //  Serial.println(" bytes");
  return max_free;
}

void dumpSysInfo()
{
  esp_chip_info_t sysinfo;
  esp_chip_info(&sysinfo);
  Serial.print("Model: ");
  Serial.print((int)sysinfo.model);
  Serial.print("; Features: 0x");
  Serial.print((int)sysinfo.features, HEX);
  Serial.print("; Cores: ");
  Serial.print((int)sysinfo.cores);
  Serial.print("; Revision: r");
  Serial.println((int)sysinfo.revision);
}

void dumpDebugBuffer(int id, char *debugBuffer)
{
  Serial.print("DEBUG: (");
  Serial.print(id);
  Serial.print(") ");
  Serial.println(debugBuffer);
  debugBuffer[0] = 0;
}

//**************************************************************************//
bool initStrands()
{
  digitalLeds_initDriver();

  for (int i = 0; i < STRANDCNT; i++)
  {
    gpioSetup(STRANDS[i].gpioNum, OUTPUT, LOW);
  }

  strand_t *strands[8];
  for (int i = 0; i < STRANDCNT; i++)
  {
    strands[i] = &STRANDS[i];
  }
  int rc = digitalLeds_addStrands(strands, STRANDCNT);
  if (rc)
  {
    Serial.print("Init rc = ");
    Serial.println(rc);
    return false;
  }

  for (int i = 0; i < STRANDCNT; i++)
  {
    strand_t *pStrand = strands[i];
    Serial.print("Strand ");
    Serial.print(i);
    Serial.print(" = ");
    Serial.print((uint32_t)(pStrand->pixels), HEX);
    Serial.println();
#if DEBUG_ESP32_DIGITAL_LED_LIB
    dumpDebugBuffer(-2, digitalLeds_debugBuffer);
#endif
  }

  return true;
}

void ledStripInit()
{
  dumpSysInfo();
  getMaxMalloc(1 * 1024, 16 * 1024 * 1024);

  if (!initStrands())
  {
    Serial.println("Init FAILURE: halting");
    while (true)
    {
      delay(100);
    }
  }
  delay(100);
}