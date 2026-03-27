
import os

os.environ["TOKENIZERS_PARALLELISM"] = "true"  # suppress tokenizer parallelism warning

LANG_EMB_OBS_KEY = "lang_emb"
TOKENIZER_NAME = "openai/clip-vit-large-patch14"

# 延迟导入 / 延迟加载，避免模块 import 时就联网下载
lang_emb_model = None
tz = None


def _get_cache_dir():
    return os.path.expanduser(
        os.path.join(os.environ.get("HF_HOME", "~/tmp"), "transformers")
    )


def _lazy_load_lang_model():
    """
    Lazy-load CLIP text encoder and tokenizer only when needed.

    This avoids triggering Hugging Face downloads during robomimic import
    for workflows that do not use language observations.
    """
    global lang_emb_model, tz

    if lang_emb_model is not None and tz is not None:
        return

    try:
        from transformers import AutoTokenizer, CLIPTextModelWithProjection
    except Exception as e:
        raise ImportError(
            "transformers is required for language embedding support, "
            "but it could not be imported."
        ) from e

    cache_dir = _get_cache_dir()

    try:
        lang_emb_model = CLIPTextModelWithProjection.from_pretrained(
            TOKENIZER_NAME,
            cache_dir=cache_dir,
        ).eval()

        tz = AutoTokenizer.from_pretrained(
            TOKENIZER_NAME,
            cache_dir=cache_dir,
            TOKENIZERS_PARALLELISM=True,
        )

    except Exception as e:
        raise RuntimeError(
            "Failed to load CLIP text model/tokenizer for language embeddings. "
            "If language observations are not needed, this file now safely "
            "avoids loading them until get_lang_emb() is called. "
            "If you do need language input, please ensure network access or "
            "pre-download the model to the local Hugging Face cache.\n"
            f"Model name: {TOKENIZER_NAME}\n"
            f"Cache dir: {cache_dir}"
        ) from e


def get_lang_emb(lang):
    """
    Convert a text string into a CLIP text embedding.

    Returns:
        None if lang is None
        torch.Tensor otherwise
    """
    if lang is None:
        return None

    _lazy_load_lang_model()

    tokens = tz(
        text=lang,
        add_special_tokens=True,
        max_length=25,
        padding="max_length",
        truncation=True,
        return_attention_mask=True,
        return_tensors="pt",
    )

    lang_emb = lang_emb_model(**tokens)["text_embeds"].detach()[0]
    return lang_emb
