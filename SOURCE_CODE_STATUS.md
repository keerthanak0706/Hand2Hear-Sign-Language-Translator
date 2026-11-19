# Phase 2 source-code status

## What the supplied Phase 2 report actually provides

The Phase 2 report describes a Raspberry Pi 5 implementation with:

- Five flex sensors read through an MCP3008 10-bit ADC over SPI.
- A recording script that saves labelled samples (default 300 samples per pose, 50 ms interval).
- CSV dataset names reported as `gesture_dataset.csv`, `gesture_dataset2.csv`, `gesture_dataset3.csv`, and `gesture_dataset5.csv`.
- Five raw sensor values expanded into 33 engineered features: five raw values, five sample-normalised values, four adjacent differences, four clipped adjacent ratios, five summary statistics, five max-position one-hot values and five min-position one-hot values.
- Random Forest classification (the report describes separate raw-reading and engineered-feature model variants).
- YOLO detection for 25 classes (`pose_1` through `pose_25`).
- Confidence-based selection, a five-frame stability filter and fixed sentence/audio mapping.
- Bluetooth speaker playback using eSpeak NG and an audio player.

## What is not present in the supplied report

The report does **not** provide the complete executable Python source files, trained `.joblib` model(s), scaler file, YOLO weights, original dataset CSV files, labelled camera image dataset, or the complete deployment configuration. Those assets cannot be recreated faithfully from descriptive text alone.

## Files to request from the project team before claiming Phase 2 is runnable

Please add the actual project files, if available, under this folder:

```text
Phase-2/
├── data/
│   ├── gesture_dataset.csv
│   ├── gesture_dataset2.csv
│   ├── gesture_dataset3.csv
│   └── gesture_dataset5.csv
├── models/
│   ├── flex_only_random_forest.joblib
│   ├── engineered_random_forest.joblib
│   ├── feature_scaler.joblib
│   └── yolo_best.pt
├── src/
│   ├── record_flex.py
│   ├── train_flex_only.py
│   ├── train_engineered_model.py
│   ├── run_flex_only.py
│   ├── run_camera_assisted.py
│   ├── features.py
│   └── sentence_audio.py
├── camera_dataset/
└── requirements.txt
```

These are recommended organisation names, not filenames verified as existing originals.

## Important consistency checks from the report

1. The recording script reportedly writes columns `little` and `gesture`; training/runtime scripts expect `pinky` and `label`. Resolve the column names consistently before training.
2. The flex-only model consumes five raw readings. The camera-assisted branch's Random Forest and scaler consume 33 engineered features. Do not load one model in the other mode.
3. Use the same feature-construction function and scaler at training and inference.
4. The documented acceptance thresholds are 0.70 (flex-only) and 0.60 (camera-assisted).
5. YOLO uses 25 pose classes named `pose_1` to `pose_25`; the matching trained weights and class mapping are needed.
6. The report describes fixed sentence playback, but the actual audio clips and final mapping file must be supplied by the team.
