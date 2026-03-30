1）逐条采集

每次采一条，文件名不同：

python /home/flowing/piper/src/imitation/no_vision_pipeline_simplified.py collect \
  --output /home/flowing/piper/data/single_demo/demo_002.hdf5 

再采第二条：

python /home/flowing/piper/src/imitation/no_vision_pipeline_simplified.py collect\
  --output /home/flowing/piper/data/test/demo_007.hdf5 

回放轨迹：
python /home/flowing/piper/src/imitation/no_vision_pipeline_simplified.py replay\
  --input /home/flowing/piper/data/test/demo_006.hdf5 

2）分别检查单轨迹 HDF5
python /home/flowing/piper/src/imitation/no_vision_pipeline_simplified.py inspect \
  --input /home/flowing/piper/data/single_demo/demo_001.hdf5

关键检查点：

action min ≥ -1
action max ≤ 1
data attrs 下有 env_args
3）合并成总训练集
python /home/flowing/piper/src/imitation/merge_hdf5.py \
  --inputs /home/flowing/piper/data/single_demo/demo_001.hdf5 \
           /home/flowing/piper/data/single_demo/demo_002.hdf5 \
           /home/flowing/piper/data/single_demo/demo_003.hdf5 \
           /home/flowing/piper/data/single_demo/demo_004.hdf5 \
           /home/flowing/piper/data/single_demo/demo_005.hdf5 \
           /home/flowing/piper/data/single_demo/demo_006.hdf5 \
           /home/flowing/piper/data/single_demo/demo_007.hdf5 \
           /home/flowing/piper/data/single_demo/demo_008.hdf5 \
           /home/flowing/piper/data/single_demo/demo_009.hdf5 \
           /home/flowing/piper/data/single_demo/demo_010.hdf5 \
  --output /home/flowing/piper/data/merge_demos/train_merged_3_28_1.hdf5

4）检查总数据集
python /home/flowing/piper/robomimic/robomimic/robomimic/scripts/get_dataset_info.py \
  --dataset /home/flowing/piper/data/merge_demos/train_merged1.hdf5

如果结构正确，前面你已经看到这个脚本会输出：

total transitions
total trajectories
Env Meta
Dataset Structure

此前它曾在 action 范围检查处失败。
现在应通过这一步。

5）生成 JSON
python /home/flowing/piper/src/imitation/no_vision_pipeline_simplified.py make-config \
  --dataset /home/flowing/piper/data/merge_demos/train_pose6_merged_3_28_1.hdf5 \
  --output /home/flowing/piper/data/json/piper_bc_rnn_3_28_1.json 


6）先跑 debug
python /home/flowing/piper/robomimic/robomimic/robomimic/scripts/train.py \
  --config /home/flowing/piper/data/json/piper_bc_rnn_3_28_1.json \
  --dataset /home/flowing/piper/data/merge_demos/train_merged_3_28_1.hdf5 \
  --debug
7）正式训练
python /home/flowing/piper/robomimic/robomimic/robomimic/scripts/train.py \
  --config /home/flowing/piper/data/json/piper_bc_rnn_3_28_1.json \
  --dataset /home/flowing/piper/data/merge_demos/train_merged_3_28_1.hdf5 


  python /home/flowing/piper/src/imitation/deploy_policy_real.py --dry-run