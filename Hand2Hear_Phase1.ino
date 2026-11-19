* Hand2Hear – Phase 1 Complete Source Code
 * Title    : Flex Sensor Gesture Detection with Threshold Classification
 * Board    : Arduino Nano 33 BLE Sense Rev2
 * IDE      : Arduino IDE 2.0 + Arduino Mbed OS Nano board package
 * Group    : Group 5 | Dept. of ECE | Acharya Institute of Technology
 * Guide    : Dr. Nataraju A B, Associate Professor
 * Year     : 2025-26
 *
 * Pin Assignments:
 *   A0 – Flex Sensor 1 (Thumb)   → WASHROOM
 *   A1 – Flex Sensor 2 (Index)   → DRINK WATER
 *   A2 – Flex Sensor 3 (Middle)  → FOOD
 *   A3 – Flex Sensor 4 (Ring)    → FRUIT
 *   A4 – Flex Sensor 5 (Little)  → Reserved for Phase 2
 *
 * Circuit: Each flex sensor is one arm of a voltage divider.
 *   3.3V → Flex Sensor → ADC Pin → 10kΩ Fixed Resistor → GND
 *
 * Operation: Reads 4 sensors, computes which (if any) is below
 *   its calibrated threshold. Uses count==1 constraint to ensure
 *   only one unambiguous gesture is output per cycle.
 */

// ── CALIBRATED THRESHOLD VALUES ─────────────────────────────────────
// Calibration formula: Threshold = (ADC_extended + ADC_flexed) / 2
// Sensor S1 (Thumb)  : Extended ~312, Flexed ~270 → Threshold 295 (±5 buffer)
// Sensor S2 (Index)  : Extended ~309, Flexed ~268 → Threshold 290 (±5 buffer)
// Sensor S3 (Middle) : Extended ~305, Flexed ~265 → Threshold 280 (±5 buffer)
// Sensor S4 (Ring)   : Extended ~261, Flexed ~220 → Threshold 240 (±5 buffer)
// NOTE: Recalibrate at the start of each session if sensors are moved.
int t1 = 295;
int t2 = 290;
int t3 = 280;
int t4 = 240;

// ── SETUP ─────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);
  while (!Serial && millis() < 3000);
  Serial.println("================================================");
  Serial.println("  Hand2Hear Phase 1 – Initialised");
  Serial.println("  Group 5 | Dept. of ECE | AIT 2025-26");
  Serial.println("================================================");
  Serial.println("Gesture Mapping:");
  Serial.println("  S1 (Thumb)  → WASHROOM");
  Serial.println("  S2 (Index)  → DRINK WATER");
  Serial.println("  S3 (Middle) → FOOD");
  Serial.println("  S4 (Ring)   → FRUIT");
  Serial.println("  None bent   → NOTHING");
  Serial.println("------------------------------------------------");
}

// ── MAIN LOOP ─────────────────────────────────────────────────────────
void loop() {
  // 1. Acquire raw ADC readings from all four active sensors
  int s1 = analogRead(A0);  // Thumb
  int s2 = analogRead(A1);  // Index
  int s3 = analogRead(A2);  // Middle
  int s4 = analogRead(A3);  // Ring

  // 2. Display raw values and thresholds for debugging / Serial Plotter
  Serial.println("─── SENSOR READINGS ───────────────────────────");
  Serial.print("  S1 (Thumb) : ");  Serial.print(s1);
  Serial.print("  | Threshold: "); Serial.println(t1);
  Serial.print("  S2 (Index) : ");  Serial.print(s2);
  Serial.print("  | Threshold: "); Serial.println(t2);
  Serial.print("  S3 (Middle): ");  Serial.print(s3);
  Serial.print("  | Threshold: "); Serial.println(t3);
  Serial.print("  S4 (Ring)  : ");  Serial.print(s4);
  Serial.print("  | Threshold: "); Serial.println(t4);

  // 3. Determine how many sensors indicate a bent state
  //    (bent = ADC value BELOW threshold, inverse sensor response)
  int count = 0;
  if (s1 < t1) count++;  // Thumb bent
  if (s2 < t2) count++;  // Index bent
  if (s3 < t3) count++;  // Middle bent
  if (s4 < t4) count++;  // Ring bent

  // 4. Classification: exactly one bent finger = valid gesture
  //    count != 1 → ambiguous state → output NOTHING
  Serial.println("─── CLASSIFICATION OUTPUT ─────────────────────");
  if (count == 1) {
    if      (s1 < t1) { Serial.println("  >> WASHROOM"); }
    else if (s2 < t2) { Serial.println("  >> DRINK WATER"); }
    else if (s3 < t3) { Serial.println("  >> FOOD"); }
    else if (s4 < t4) { Serial.println("  >> FRUIT"); }
  } else if (count == 0) {
    Serial.println("  >> NOTHING (no gesture)");
  } else {
    Serial.print("  >> NOTHING (ambiguous – ");
    Serial.print(count);
    Serial.println(" sensors active)");
  }
  Serial.println("───────────────────────────────────────────────");

  // 5. Wait 1 second before next reading cycle
  delay(1000);
}

// ── END OF PHASE 1 CODE ───────────────────────────────────────────────
