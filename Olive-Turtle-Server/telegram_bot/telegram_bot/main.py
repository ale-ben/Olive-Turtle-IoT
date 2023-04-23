import configuration
import logging
import json
from telegram import Update, MenuButtonCommands, Chat
from telegram.ext import (
	filters,
	MessageHandler,
	ApplicationBuilder,
	CommandHandler,
	ContextTypes,
)

logging.basicConfig(
	format="%(asctime)s - %(name)s - %(levelname)s - %(message)s",
	level=logging.INFO)

async def authenticate(update: Update, context: ContextTypes.DEFAULT_TYPE):
	msg = f"Access denied. Please either authorize user {update.effective_user.id} or chat {update.effective_chat.id}"
	await context.bot.send_message(chat_id=update.effective_chat.id,
								   text=msg)
	return False

async def start(update: Update, context: ContextTypes.DEFAULT_TYPE):
	if await authenticate(update, context):
		await context.bot.send_message(chat_id=update.effective_chat.id,
								   text="I'm a bot, please talk to me!")


async def echo(update: Update, context: ContextTypes.DEFAULT_TYPE):
	await update.effective_chat.set_menu_button(menu_button=MenuButtonCommands())
	await context.bot.send_message(chat_id=update.effective_chat.id,
								   text=update.message.text)


async def caps(update: Update, context: ContextTypes.DEFAULT_TYPE):
	text_caps = " ".join(context.args).upper()
	await context.bot.send_message(chat_id=update.effective_chat.id,
								   text=text_caps)

async def unknown(update: Update, context: ContextTypes.DEFAULT_TYPE):
	await context.bot.send_message(chat_id=update.effective_chat.id, text="Sorry, I didn't understand that command.")


if __name__ == "__main__":
	application = ApplicationBuilder().token(configuration.TELEGRAM_API_KEY).build()

	#application.bot.set_chat_menu_button(menu_button=MenuButtonCommands())
	application.bot.set_chat_menu_button()

	start_handler = CommandHandler("start", start)
	application.add_handler(start_handler)
	echo_handler = MessageHandler(filters.TEXT & (~filters.COMMAND), echo)
	application.add_handler(echo_handler)

	caps_handler = CommandHandler("caps", caps)
	application.add_handler(caps_handler)

	unknown_handler = MessageHandler(filters.COMMAND, unknown)
	application.add_handler(unknown_handler)

	application.run_polling()
